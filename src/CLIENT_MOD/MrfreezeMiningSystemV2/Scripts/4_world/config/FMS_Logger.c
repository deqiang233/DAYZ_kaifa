class LoggingUtility extends PluginBase {
    static const string FreezeMiningFolder = "$profile:FreezeMining/";
    static const string LogsFolder = "$profile:FreezeMining/Logs/";
    static const string MiningFolder = "$profile:FreezeMining/Mining/";
    static int lastLogTime = 0;
    static const int logInterval = 5000;
    static bool directoriesEnsured = false;
    static string currentLogFile = "";
    static string currentDebugLogFile = "";
    static bool logsEnabled = true;
    static bool debugEnabled = false;
    static int keepLogDays = 7;
    static bool settingsLoaded = false;
    static bool oldLogsCleanedUp = false;

    static void LoadSettings() {
        if (!settingsLoaded) {
            FreezeCraftingSettings settings = FreezeCraftingSettings.Load();
            if (settings) {
                logsEnabled = settings.EnableLogs;
                debugEnabled = settings.EnableDebug;
                keepLogDays = settings.KeepLogDays;
            }
            settingsLoaded = true;
        }
    }

    static void LogToFileFM(string message, bool bypassRateLimit = false) {
        LoadSettings();

        if (!logsEnabled) {
            return;
        }

        EnsureDirectoriesExist();

        if (currentLogFile == "") {
            currentLogFile = LogsFolder + "FreezeMining_" + GetTimestampForFile() + ".log";
            CleanupOldLogs();
        }

        int currentTime = GetGame().GetTickTime() * 1000;

        if (!bypassRateLimit && currentTime - lastLogTime < logInterval) {
            return;
        }

        lastLogTime = currentTime;

        FileHandle logFile = OpenFile(currentLogFile, FileMode.APPEND);

        if (logFile != 0) {
            string timeStamp = GetDateAndTime();
            FPrintln(logFile, "[" + timeStamp + "] " + message);
            CloseFile(logFile);
        } else {
            Print("[Freeze_MiningLogs] ERROR: Failed to open log file: " + currentLogFile);
        }
    }

    static void LogDebug(string message) {
        if (!GetGame().IsServer()) {
            return;
        }

        LoadSettings();

        if (!debugEnabled) {
            return;
        }

        EnsureDirectoriesExist();

        if (currentDebugLogFile == "") {
            currentDebugLogFile = LogsFolder + "FreezeMiningDebug_" + GetTimestampForFile() + ".log";
        }

        FileHandle debugFile = OpenFile(currentDebugLogFile, FileMode.APPEND);

        if (debugFile != 0) {
            string timeStamp = GetDateAndTime();
            FPrintln(debugFile, "[" + timeStamp + "] " + message);
            CloseFile(debugFile);
        } else {
            Print("[Freeze_MiningDebug] ERROR: Failed to open debug log file: " + currentDebugLogFile);
        }
    }

    static void EnsureDirectoriesExist() {
        if (!directoriesEnsured) {
            EnsureDirectoryExists(FreezeMiningFolder);
            EnsureDirectoryExists(LogsFolder);
            EnsureDirectoryExists(MiningFolder);
            directoriesEnsured = true;
        }
    }

    static void EnsureDirectoryExists(string path) {
        if (!FileExist(path)) {
            MakeDirectory(path);
            Print("[Freeze_MiningLogs] Created directory: " + path);
        }
    }

    static string GetDateAndTime() {
        int year, month, day, hour, minute, second;
        GetYearMonthDay(year, month, day);
        GetHourMinuteSecond(hour, minute, second);

        string formattedDate = year.ToString() + "-" + FormatWithLeadingZero(month) + "-" + FormatWithLeadingZero(day);
        string formattedTime = FormatWithLeadingZero(hour) + ":" + FormatWithLeadingZero(minute) + ":" + FormatWithLeadingZero(second);

        return formattedDate + " " + formattedTime;
    }

    static string GetTimestampForFile() {
        int year, month, day, hour, minute, second;
        GetYearMonthDay(year, month, day);
        GetHourMinuteSecond(hour, minute, second);

        return year.ToString() + "_" + FormatWithLeadingZero(month) + "_" + FormatWithLeadingZero(day) + "_" + FormatWithLeadingZero(hour) + "_" + FormatWithLeadingZero(minute) + "_" + FormatWithLeadingZero(second);
    }

    static string FormatWithLeadingZero(int value) {
        if (value < 10) {
            return "0" + value.ToString();
        }
        return value.ToString();
    }

    static void CleanupOldLogs() {
        if (oldLogsCleanedUp || keepLogDays <= 0) {
            return;
        }

        oldLogsCleanedUp = true;

        int currentYear, currentMonth, currentDay;
        GetYearMonthDay(currentYear, currentMonth, currentDay);

        int cutoffYear = currentYear;
        int cutoffMonth = currentMonth;
        int cutoffDay = currentDay - keepLogDays;

        while (cutoffDay <= 0) {
            cutoffMonth = cutoffMonth - 1;
            if (cutoffMonth <= 0) {
                cutoffMonth = 12;
                cutoffYear = cutoffYear - 1;
            }
            cutoffDay = cutoffDay + GetDaysInMonth(cutoffYear, cutoffMonth);
        }

        Print("[Freeze_MiningLogs] Cleaning up logs older than " + keepLogDays.ToString() + " days (before " + cutoffYear.ToString() + "-" + cutoffMonth.ToString() + "-" + cutoffDay.ToString() + ")");

        string fileName;
        FileAttr fileAttr;

        FindFileHandle findHandle = FindFile(LogsFolder + "FreezeMining*.log", fileName, fileAttr, 0);

        if (findHandle)
        {
            while (fileName != "")
            {
                if (IsLogFileOld(fileName, cutoffYear, cutoffMonth, cutoffDay))
                {
                    DeleteFile(LogsFolder + fileName);
                    Print("[Freeze_MiningLogs] Deleted old log file: " + fileName);
                }
                
                if (!FindNextFile(findHandle, fileName, fileAttr))
                {
                    break;
                }
            }
            
            CloseFindFile(findHandle);
        }
    }

    static bool IsLogFileOld(string fileName, int cutoffYear, int cutoffMonth, int cutoffDay)
    {
        TStringArray parts = new TStringArray;
        fileName.Split("_", parts);

        if (parts.Count() < 4)
        {
            return false;
        }

        int yearIndex = 1;
        if (fileName.IndexOf("FreezeMiningDebug") >= 0)
        {
            yearIndex = 1;
        }

        int fileYear = parts[yearIndex].ToInt();
        int fileMonth = parts[yearIndex + 1].ToInt();
        int fileDay = parts[yearIndex + 2].ToInt();

        if (fileYear < cutoffYear)
        {
            return true;
        }

        if (fileYear == cutoffYear)
        {
            if (fileMonth < cutoffMonth)
            {
                return true;
            }
            if (fileMonth == cutoffMonth && fileDay < cutoffDay)
            {
                return true;
            }
        }

        return false;
    }

    static int GetDaysInMonth(int year, int month) {
        if (month == 2) {
            if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
                return 29;
            }
            return 28;
        }

        if (month == 4 || month == 6 || month == 9 || month == 11) {
            return 30;
        }

        return 31;
    }
};
