#include "Zero/Utils/Utils.h"
#include "Zero/Application/Application.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <commdlg.h>


std::string Zero::FileDialog::OpenFile(const char* filter)
{
    OPENFILENAMEA openFileName;
    CHAR fileSize[260]{ 0 };

    ZeroMemory(&openFileName, sizeof(OPENFILENAMEA));
    openFileName.lStructSize = sizeof(OPENFILENAME);
    openFileName.hwndOwner = glfwGetWin32Window(Application::Get().GetWindow().GetWindowHandle());
    openFileName.lpstrFile = fileSize;
    openFileName.nMaxFile = sizeof(fileSize);
    openFileName.lpstrFilter = filter;
    openFileName.nFilterIndex = 1;
    openFileName.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

    if (GetOpenFileNameA(&openFileName) == TRUE)
    {
        return openFileName.lpstrFile;
    }

    return std::string{};
}


std::string Zero::FileDialog::SaveFile(const char* filter)
{
    OPENFILENAMEA openFileName;
    CHAR fileSize[260]{ 0 };

    ZeroMemory(&openFileName, sizeof(OPENFILENAMEA));
    openFileName.lStructSize = sizeof(OPENFILENAME);
    openFileName.hwndOwner = glfwGetWin32Window(Application::Get().GetWindow().GetWindowHandle());
    openFileName.lpstrFile = fileSize;
    openFileName.nMaxFile = sizeof(fileSize);
    openFileName.lpstrFilter = filter;
    openFileName.nFilterIndex = 1;
    openFileName.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

    if (GetSaveFileNameA(&openFileName) == TRUE)
    {
        return openFileName.lpstrFile;
    }

    return std::string{};
}
