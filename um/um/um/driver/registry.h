#pragma once

class CRegistry {

private:

    HKEY hKey;

public:

    CRegistry()
    {
        hKey = NULL;
    }
    CRegistry(HKEY hkey, LPCSTR SubKey)
    {
        if (RegOpenKeyExA(hkey, SubKey, 0, KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS)
        {
            HKEY pHKEY;

            if (CreateKey(hkey, SubKey, &pHKEY) == ERROR_SUCCESS)
                RegCloseKey(pHKEY);
        }
    }
    CRegistry(HKEY hkey, LPCWSTR SubKey)
    {
        if (RegOpenKeyExW(hkey, SubKey, 0, KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS)
        {
            HKEY pHKEY;

            if (CreateKey(hkey, SubKey, &pHKEY) == ERROR_SUCCESS)
                RegCloseKey(pHKEY);
        }
    }

    LSTATUS CreateKey(HKEY hkey, LPCWSTR SubKey, HKEY* pHkey)
    {
        return RegCreateKeyW(hkey, SubKey, pHkey);
    }
    LSTATUS CreateKey(HKEY hkey, LPCSTR SubKey, HKEY* pHkey)
    {
        return RegCreateKeyA(hkey, SubKey, pHkey);
    }

    ~CRegistry()
    {
        RegCloseKey(hKey);
    }

    ULONG ReadDWORD(LPCSTR lpValue)
    {
        ULONG val;
        ULONG dataSize = sizeof(val);
        if (RegGetValueA(hKey, NULL, lpValue, RRF_RT_DWORD, nullptr, &val, &dataSize)
            == ERROR_SUCCESS) {
            return val;
        }
        else {

            return 0;
        }
    }
    ULONG ReadDWORD(LPCWSTR lpValue)
    {
        ULONG val;
        ULONG dataSize = sizeof(val);
        if (RegGetValueW(hKey, NULL, lpValue, RRF_RT_DWORD, nullptr, &val, &dataSize)
            == ERROR_SUCCESS) {
            return val;
        }
        else {

            return 0;
        }
    }
    ULONG ReadDWORD(HKEY hkey, LPCSTR lpSubKey, LPCSTR lpValue)
    {
        ULONG val;
        ULONG dataSize = sizeof(val);
        if (RegGetValueA(hkey, lpSubKey, lpValue, RRF_RT_DWORD, nullptr, &val, &dataSize)
            == ERROR_SUCCESS) {
            return val;
        }
        else {

            return 0;
        }
    }
    ULONG ReadDWORD(HKEY hkey, LPCWSTR lpSubKey, LPCWSTR lpValue)
    {
        ULONG val;
        ULONG dataSize = sizeof(val);
        if (RegGetValueW(hkey, lpSubKey, lpValue, RRF_RT_DWORD, nullptr, &val, &dataSize)
            == ERROR_SUCCESS) {
            return val;
        }
        else {

            return 0;
        }
    }

    BOOL ReadBOOL(LPCSTR lpValue)
    {
        ULONG val;
        ULONG dataSize = sizeof(val);
        if (RegGetValueA(hKey, NULL, lpValue, RRF_RT_DWORD, nullptr, &val, &dataSize)
            == ERROR_SUCCESS) {
            return static_cast<BOOL>(val);
        }
        else {

            return FALSE;
        }
    }
    BOOL ReadBOOL(LPCWSTR lpValue)
    {
        ULONG val;
        ULONG dataSize = sizeof(val);
        if (RegGetValueW(hKey, NULL, lpValue, RRF_RT_DWORD, nullptr, &val, &dataSize)
            == ERROR_SUCCESS) {
            return static_cast<BOOL>(val);
        }
        else {

            return FALSE;
        }
    }
    BOOL ReadBOOL(HKEY hkey, LPCSTR lpSubKey, LPCSTR lpValue)
    {
        ULONG val;
        ULONG dataSize = sizeof(val);
        if (RegGetValueA(hkey, lpSubKey, lpValue, RRF_RT_DWORD, nullptr, &val, &dataSize)
            == ERROR_SUCCESS) {
            return static_cast<BOOL>(val);
        }
        else {

            return FALSE;
        }
    }
    BOOL ReadBOOL(HKEY hkey, LPCWSTR lpSubKey, LPCWSTR lpValue)
    {
        ULONG val;
        ULONG dataSize = sizeof(val);
        if (RegGetValueW(hkey, lpSubKey, lpValue, RRF_RT_DWORD, nullptr, &val, &dataSize)
            == ERROR_SUCCESS) {
            return static_cast<BOOL>(val);
        }
        else {

            return FALSE;
        }
    }

    DWORD64 ReadDWORD64(LPCSTR lpValue)
    {
        DWORD64 val;
        ULONG dataSize = sizeof(val);
        if (RegGetValueA(hKey, NULL, lpValue, RRF_RT_QWORD, nullptr, &val, &dataSize)
            == ERROR_SUCCESS) {
            return val;
        }
        else {

            return 0;
        }
    }
    DWORD64 ReadDWORD64(LPCWSTR lpValue)
    {
        DWORD64 val;
        ULONG dataSize = sizeof(val);
        if (RegGetValueW(hKey, NULL, lpValue, RRF_RT_QWORD, nullptr, &val, &dataSize)
            == ERROR_SUCCESS) {
            return val;
        }
        else {

            return 0;
        }
    }
    DWORD64 ReadDWORD64(HKEY hkey, LPCSTR lpSubKey, LPCSTR lpValue)
    {
        DWORD64 val;
        ULONG dataSize = sizeof(val);
        if (RegGetValueA(hkey, lpSubKey, lpValue, RRF_RT_QWORD, nullptr, &val, &dataSize)
            == ERROR_SUCCESS) {
            return val;
        }
        else {

            return 0;
        }
    }
    DWORD64 ReadDWORD64(HKEY hkey, LPCWSTR lpSubKey, LPCWSTR lpValue)
    {
        DWORD64 val;
        ULONG dataSize = sizeof(val);
        if (RegGetValueW(hkey, lpSubKey, lpValue, RRF_RT_QWORD, nullptr, &val, &dataSize)
            == ERROR_SUCCESS) {
            return val;
        }
        else {

            return 0;
        }
    }

    PCHAR ReadString(LPCSTR lpValue)
    {
        PCHAR val = new CHAR[260];
        SecureZeroMemory(val, 260);
        ULONG dataSize = 260 - 1;
        if (RegGetValueA(hKey, NULL, lpValue, RRF_RT_REG_SZ, NULL, val, &dataSize)
            == ERROR_SUCCESS) {
            return val;
        }
        else {

            return (PCHAR)0;
        }
    }
    PCHAR ReadString(LPCWSTR lpValue)
    {
        PCHAR val = new CHAR[260];
        SecureZeroMemory(val, 260);
        ULONG dataSize = 260 - 1;
        if (RegGetValueW(hKey, NULL, lpValue, RRF_RT_REG_SZ, NULL, val, &dataSize)
            == ERROR_SUCCESS) {
            return val;
        }
        else {

            return (PCHAR)0;
        }
    }
    PCHAR ReadString(HKEY hkey, LPCSTR lpSubKey, LPCSTR lpValue)
    {
        PCHAR val = new CHAR[260];
        SecureZeroMemory(val, 260);
        ULONG dataSize = 260 - 1;
        if (RegGetValueA(hkey, lpSubKey, lpValue, RRF_RT_REG_SZ, NULL, val, &dataSize)
            == ERROR_SUCCESS) {
            return val;
        }
        else {

            return (PCHAR)0;
        }
    }
    PCHAR ReadString(HKEY hkey, LPCWSTR lpSubKey, LPCWSTR lpValue)
    {
        PCHAR val = new CHAR[260];
        SecureZeroMemory(val, 260);
        ULONG dataSize = 260 - 1;
        if (RegGetValueW(hkey, lpSubKey, lpValue, RRF_RT_REG_SZ, NULL, val, &dataSize)
            == ERROR_SUCCESS) {
            return val;
        }
        else {

            return (PCHAR)0;
        }
    }

    VOID WriteString(LPCSTR lpValue, PCCH Buffer)
    {
        if (hKey && hKey != INVALID_HANDLE_VALUE)
        {
            RegSetValueExA(hKey, lpValue, 0, REG_SZ, (PUCHAR)Buffer, static_cast<ULONG>(strlen(Buffer)));
        }
    }

    VOID WriteDWORD(LPCSTR lpValue, ULONG Buffer)
    {
        if (hKey && hKey != INVALID_HANDLE_VALUE)
        {
            RegSetValueExA(hKey, lpValue, 0, REG_DWORD, reinterpret_cast<BYTE*>(&Buffer), sizeof(ULONG));
        }
    }
    VOID WriteDWORD(LPCWSTR lpValue, ULONG Buffer)
    {
        if (hKey && hKey != INVALID_HANDLE_VALUE)
        {
            RegSetValueExW(hKey, lpValue, 0, REG_DWORD, reinterpret_cast<BYTE*>(&Buffer), sizeof(ULONG));
        }
    }
    VOID WriteDWORD(HKEY hkey, LPCSTR lpSubKey, LPCSTR lpValue, ULONG Buffer)
    {
        HKEY hkey_;
        RegOpenKeyExA(hkey, lpSubKey, 0, KEY_ALL_ACCESS, &hkey_);
        if (hkey_ && hkey_ != INVALID_HANDLE_VALUE)
        {
            RegSetValueExA(hkey_, lpValue, 0, REG_DWORD, reinterpret_cast<BYTE*>(&Buffer), sizeof(ULONG));
            RegCloseKey(hkey_);
        }
    }
    VOID WriteDWORD(HKEY hkey, LPCWSTR lpSubKey, LPCWSTR lpValue, ULONG Buffer)
    {
        HKEY hkey_;
        RegOpenKeyExW(hkey, lpSubKey, 0, KEY_ALL_ACCESS, &hkey_);
        if (hkey_ && hkey_ != INVALID_HANDLE_VALUE)
        {
            RegSetValueExW(hkey_, lpValue, 0, REG_DWORD, reinterpret_cast<BYTE*>(&Buffer), sizeof(ULONG));
            RegCloseKey(hkey_);
        }
    }

    VOID WriteDWORD64(LPCSTR lpValue, DWORD64 Buffer)
    {
        if (hKey && hKey != INVALID_HANDLE_VALUE)
        {
            RegSetValueExA(hKey, lpValue, 0, REG_QWORD, reinterpret_cast<BYTE*>(&Buffer), sizeof(DWORD64));
        }
    }
    VOID WriteDWORD64(LPCWSTR lpValue, DWORD64 Buffer)
    {
        if (hKey && hKey != INVALID_HANDLE_VALUE)
        {
            RegSetValueExW(hKey, lpValue, 0, REG_QWORD, reinterpret_cast<BYTE*>(&Buffer), sizeof(DWORD64));
        }
    }
    VOID WriteDWORD64(HKEY hkey, LPCSTR lpSubKey, LPCSTR lpValue, DWORD64 Buffer)
    {
        HKEY hkey_;
        RegOpenKeyExA(hkey, lpSubKey, 0, KEY_ALL_ACCESS, &hkey_);
        if (hkey_ && hkey_ != INVALID_HANDLE_VALUE) {
            RegSetValueExA(hkey_, lpValue, 0, REG_QWORD, reinterpret_cast<BYTE*>(&Buffer), sizeof(DWORD64));
            RegCloseKey(hkey_);
        }
    }
    VOID WriteDWORD64(HKEY hkey, LPCWSTR lpSubKey, LPCWSTR lpValue, DWORD64 Buffer)
    {
        HKEY hkey_;
        RegOpenKeyExW(hkey, lpSubKey, 0, KEY_ALL_ACCESS, &hkey_);
        if (hkey_ && hkey_ != INVALID_HANDLE_VALUE) {
            RegSetValueExW(hkey_, lpValue, 0, REG_QWORD, reinterpret_cast<BYTE*>(&Buffer), sizeof(DWORD64));
            RegCloseKey(hkey_);
        }
    }

    VOID DeleteValue(LPCSTR lpValueName)
    {
        if (hKey && hKey != INVALID_HANDLE_VALUE)
        {
            RegDeleteValueA(hKey, lpValueName);
        }
    }
    VOID DeleteValue(LPCWSTR lpValueName)
    {
        if (hKey && hKey != INVALID_HANDLE_VALUE)
        {
            RegDeleteValueW(hKey, lpValueName);
        }
    }
    VOID DeleteValue(HKEY hkey, LPCSTR lpSubKey, LPCSTR lpValueName)
    {
        RegDeleteKeyValueA(hkey, lpSubKey, lpValueName);
    }
    VOID DeleteValue(HKEY hkey, LPCWSTR lpSubKey, LPCWSTR lpValueName)
    {
        RegDeleteKeyValueW(hkey, lpSubKey, lpValueName);
    }

    VOID DeleteKey(LPCSTR lpSubKey)
    {
        if (hKey && hKey != INVALID_HANDLE_VALUE) {
            RegDeleteKeyA(hKey, lpSubKey);
        }
    }
    VOID DeleteKey(LPCWSTR lpSubKey)
    {
        if (hKey && hKey != INVALID_HANDLE_VALUE) {
            RegDeleteKeyW(hKey, lpSubKey);
        }
    }
    VOID DeleteKey(HKEY hkey, LPCSTR lpSubKey)
    {
        RegDeleteKeyA(hkey, lpSubKey);
    }
    VOID DeleteKey(HKEY hkey, LPCWSTR lpSubKey)
    {
        RegDeleteKeyW(hkey, lpSubKey);
    }
};