using System;
using System.IO;
using System.Runtime.InteropServices;
using System.Security.Principal;
using System.Threading.Tasks;

namespace TMPR
{
    class TempRecycler
    {
        static void Main(string[] args)
        {
            if (!IsAdministrator())
            {
                CleanUserTempFiles();
                ClearRecyclerBin();
            }
            else
            {
                CleanSystemTemp();
                ClearUserTempFiles();
                ClearRecyclerBin();
            }
        }

        public static IsAdministrator()
        {
            var id = WindowsIdentity.GetCurrent();
            var principal = new WindowsPrincipal(id);
            return principal.IsInRole(WindowsBuiltInRole.Administrator);
        }

        enum RECYCLE_FLAGS : uint
        {
            RF_NO_CONFIRMATION = 0x00000001,
            RF_NO_PROGRESS_UI = 0x00000002,
            RF_NO_SOUND = 0x0000003
        }

        private static void CleanSystemTemp()
        {
            try
            {
                var SystemTemp = Environment.GetEnvironmentVariable("TEMP", EnvironmentVariableTarget.Machine);
                var SystemTempFiles = Directory.GetFiles(SystemTemp);

                foreach (var fil in SystemTempFiles)
                {
                    try
                    {
                        File.SetAttributes(fil, FileAttributes.Normal);
                        File.Delete(fil);
                    }
                    catch (Exception e)
                    {
                        if (e is UnauthorizedAccessException)
                        {
                            continue;
                        }
                    }
                }
            } 
            catch
            {
                Console.WriteLine(e);
                Task.Delay(5000).Wait();
                Environment.Exit(0);
            } 
        }

        private static void CleanUserTempFiles()
        {
            try
            {
                var userTemp = Environment.GetEnvironmentVariable("TEMP");
                var userTempFiles = Directory.GetFiles(userTemp);

                foreach (var file in userTempFiles)
                {
                    try
                    {
                        File.SetAttributes(file, FileAttributes.Normal);
                        File.Delete(file);
                    }
                    catch (Exception e)
                    {
                        if (e is UnauthorizedAccessException)
                        {
                            continue;
                        }
                    }
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                Task.Delay(5000).Wait();
                Environment.Exit(0); 
            }
        }

        [DllImport("Shell32.dll", CharSet = CharSet.Unicode)]
        static extern uint ShellEmptyRecycleBin(IntPtr hwnd, string RootPath, RECYCLE_FLAGS dwFlags);

        private static void ClearRecyclerBin()
        {
            try
            {
                uint isSucess = ShellEmptyRecycleBin(IntPtr.Zero, null, RECYCLE_FLAGS.RF_NO_CONFIRMATION);
                Console.WriteLine("[>] Cleared recycle bin succesfully.");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex);
                Task.Delay(5000).Wait();
                Environment.Exit(0);
            }
        }
    }
}