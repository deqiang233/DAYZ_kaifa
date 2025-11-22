class BSHC_Log
{
    private static ref BSHC_Log instance;
    private string m_LogFileNameBase;    
    private string m_LogDirectory;
    private string m_ComponentIdentifier;


    void BSHC_Log(string componentName = "BSHC_HackedCrate")
    {
        m_ComponentIdentifier = componentName;
        m_LogDirectory = "$profile:\\Bastardo_HC\\logs"; 

        if (!FileExist(m_LogDirectory))
        {
            Print("[BSHC_Log Constructor] Log directory does not exist, attempting to create: " + m_LogDirectory);
            if (!MakeDirectory(m_LogDirectory))
            {
                Print("[BSHC_Log Constructor ERROR] CRITICAL: Failed to create directory: " + m_LogDirectory + ". Logging will likely fail.");
            }
            else
            {
                Print("[BSHC_Log Constructor] Successfully created directory: " + m_LogDirectory);
            }
        }

        int year, month, day, hour, minute, second;
        GetYearMonthDayUTC(year, month, day); 
        GetHourMinuteSecondUTC(hour, minute, second);
        string sessionTimestamp = string.Format("%1_%2_%3_%4_%5_%6", 
            year.ToStringLen(4), month.ToStringLen(2), day.ToStringLen(2), 
            hour.ToStringLen(2), minute.ToStringLen(2), second.ToStringLen(2));
        
        m_LogFileNameBase = m_LogDirectory + "\\" + m_ComponentIdentifier + "_Session_" + sessionTimestamp;
        Print("[BSHC_Log Constructor] Log file name base for this session: " + m_LogFileNameBase + ".log");
    }

    static BSHC_Log GetInstance(string componentName = "BSHC_HackedCrate")
    {
        if (!instance)
        {
            Print("[BSHC_Log GetInstance] No instance exists, creating new BSHC_Log for component: " + componentName);
            instance = new BSHC_Log(componentName);
        }
        return instance;
    }

    private void WriteLineToLog(string level, string message)
    {
        if (m_LogFileNameBase == "") 
        {
            Print("[BSHC_Log WriteLineToLog ERROR] Log file name base not initialized. Message: [" + level + "] " + message);
            return;
        }

        string currentTimestamp = GetFormattedTimestamp();
        string logEntry = currentTimestamp + " [" + level + "] " + message;
        string fullLogPath = m_LogFileNameBase + ".log"; 

        FileHandle fileHandle = OpenFile(fullLogPath, FileMode.APPEND);
        
        if (fileHandle == 0) 
        {

            Print("[BSHC_Log WriteLineToLog ERROR] Failed to open/create log file: " + fullLogPath + ". Message: " + logEntry);
            Print("[BSHC_Log RPT FALLBACK] " + logEntry);
            return;
        }

        FPrintln(fileHandle, logEntry);
        CloseFile(fileHandle);
    }

    void Info(string message)
    {
        WriteLineToLog("INFO", message);
    }

    void Warning(string message)
    {
        WriteLineToLog("WARNING", message);
    }

    void Error(string message)
    {
        WriteLineToLog("ERROR", message);
    }

    private string GetFormattedTimestamp()
    {
        int year, month, day, hour, minute, second;
        GetYearMonthDayUTC(year, month, day);
        GetHourMinuteSecondUTC(hour, minute, second);
        return string.Format("%1-%2-%3 %4:%5:%6", 
            year.ToStringLen(4), month.ToStringLen(2), day.ToStringLen(2), 
            hour.ToStringLen(2), minute.ToStringLen(2), second.ToStringLen(2));
    }

    void ~BSHC_Log()
    {
        Print("[BSHC_Log Destructor] BSHC_Log instance for " + m_ComponentIdentifier + " is being destroyed.");
    }
}