#include "my_common.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, PSTR, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

typedef struct MyStrView {
    char* begin;
    size_t len;
} MyStrView;

void MyStrView_reset(MyStrView* view) {
    view->begin = NULL;
    view->len = 0;
}

void MyStrView_c_str(MyStrView* view, char* buf, size_t bufSize) {
    memcpy_s(buf, bufSize, view->begin, view->len);
    if (bufSize > view->len) {
        buf[view->len] = '\0';
    }
    buf[bufSize - 1] = '\0';
}

void MyStrView_substr(MyStrView* dst, MyStrView* src, int st, size_t count) {
    if (count <= 0) return;

    if (src->len <= st) {
        return;
    }

    char* p = src->begin + st;
    char* srcEnd = src->begin + src->len;
    char* dstEnd = p + count;

    dst->begin = p;
    size_t dstLen = dstEnd - p;
    dst->len = myMin(count, dstLen);
}

void MyStrView_print(MyStrView* view) {
    char dirNameBuf[MAX_PATH + 1];
    MyStrView_c_str(view, dirNameBuf, sizeof(dirNameBuf));
    printf("%s\n", dirNameBuf);
}

void g_currentExePath(char* buf, size_t bufSize) {
    GetModuleFileName(NULL, buf, bufSize);
}

MyStrView g_dirName(MyStrView path) {
    char* begin = path.begin;
    char* end   = begin + path.len;

    MyStrView ret;
    ret.begin = NULL;
    ret.len   = 0;

    for (char* c = end; c != begin; c--) {
        if (*c == '/' || *c == '\\') {
            ret.begin = begin;
            ret.len   = c - begin;
            break;
        }
    }
    return ret;
}

BOOL g_getCurrentDir(char* buf, size_t bufSize) {
    if (!GetCurrentDirectory(bufSize, buf)) {
        printf("GetCurrentDirectory error");
        return FALSE;
    }
    return TRUE;
}

BOOL g_setCurrentDir(const char* dir) {
    if (!SetCurrentDirectory(dir)) {
        printf("SetCurrentDirectory error");
        return FALSE;
    }
    return TRUE;
}

void g_setWorkingDir() {
    char tmp[MAX_PATH + 1];
    g_currentExePath(tmp, sizeof(tmp));

#if _DEBUG
    printf("%s\n", tmp);
    printf("MY_CMAKE_BIN_DIR: %s\n", MY_CMAKE_BIN_DIR);
#endif

    static const char* kPrefix = MY_CMAKE_BIN_DIR;
    const size_t kPerfixSize = strlen(kPrefix);

    MyStrView path;
    path.begin = tmp;
    path.len = strlen(tmp);

    MyStrView dirName = g_dirName(path);

#if _DEBUG
    MyStrView_print(&dirName);
#endif

    char dirNameBuf[MAX_PATH + 1];
    MyStrView_c_str(&dirName, dirNameBuf, sizeof(dirNameBuf));

    MyStrView relativePath;
    MyStrView_reset(&relativePath);

    size_t st = kPerfixSize + 1;
    size_t count = dirName.len - st;
    MyStrView_substr(&relativePath, &dirName, st, count);

#if _DEBUG
    MyStrView_print(&relativePath);
    printf("dirNameBuf: %s\n", dirNameBuf);
#endif

    char relativePathBuf[MAX_PATH + 1];
    MyStrView_c_str(&relativePath, relativePathBuf, sizeof(relativePathBuf));

    char newDir[MAX_PATH + 1];
    snprintf(newDir, sizeof(newDir), "%s/../../../../%s/../", dirNameBuf, relativePathBuf);

#if _DEBUG
    printf("set current dir: %s\n", newDir);
#endif

    g_setCurrentDir(newDir);

#if _DEBUG
    g_getCurrentDir(tmp, sizeof(tmp));
    printf("\ncurrent dir: %s\n", tmp);
#endif
}

// -------------------------------------------------
#if _DEBUG
	#pragma comment( linker, "/subsystem:console" )
int main(int argc, const char** argv) {
    g_setWorkingDir();

	return WinMain(GetModuleHandle(NULL), NULL, GetCommandLineA(), SW_SHOWDEFAULT);
}
#else
	#pragma comment( linker, "/subsystem:windows" )
#endif