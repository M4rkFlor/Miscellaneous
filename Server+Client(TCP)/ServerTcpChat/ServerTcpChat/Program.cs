using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;



namespace ServerTcpChat
{
    class Program
    {
        static void Main(string[] args)
        {
            //for local hosting
            //use hostname 2600:8801:b500:193:80c6:9084:13ad:572f or ip68-6-221-21.sd.sd.cox.net or 68.6.221.21 my local is 10.0.1.8
            //IPAddress ip = Dns.GetHostEntry("localhost").AddressList[0];
            //hosting for off LAN connections
            IPAddress ip = IPAddress.Parse("10.0.1.8");
            TcpListener server = new TcpListener(ip, 8080);
            TcpClient ConnectedClient = default(TcpClient);

            try
            {
                server.Start();
                Console.WriteLine("Server started...");
                
            }catch(Exception ex)
            {
                Console.WriteLine(ex.ToString());
                Console.Read();
            }

            while (true)
            {
                //blocks and wait for a connection.
                ConnectedClient = server.AcceptTcpClient();
                Console.WriteLine("Someone connected...");

                byte[] reciveBuffer = new byte[100];
                NetworkStream stream = ConnectedClient.GetStream();

                stream.Read(reciveBuffer, 0, reciveBuffer.Length);


                //string msg = Encoding.ASCII.GetString(reciveBuffer, 0, reciveBuffer.Length);
                StringBuilder msg = new StringBuilder();

                foreach (byte b in reciveBuffer)
                {
                    if (b.Equals(00))
                    {
                        break;
                    }
                    else {
                        msg.Append(Convert.ToChar(b).ToString());
                    }
                        

                }
                //Sends Message Back To Connected Client
                byte[]  sendData = Encoding.ASCII.GetBytes("I Have Recived Your Message Have you Recived Mine?");
                stream.Write(sendData, 0, sendData.Length);
            }



        }
    }
}
