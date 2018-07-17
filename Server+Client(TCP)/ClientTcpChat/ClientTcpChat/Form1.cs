using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;

namespace ClientTcpChat
{
    public partial class Form1 : Form
    {
        //use hostname 2600:8801:b500:193:80c6:9084:13ad:572f or ip68-6-221-21.sd.sd.cox.net or 68.6.221.21 my local is 10.0.1.8
        //string serverIP = "localhost";
        //connecting to someone not in same network;
        string serverIP = IPAddress.Parse("68.6.221.21").ToString();
        int port = 8080;
        int attempts = 0;
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                TcpClient client = new TcpClient(serverIP, port);


                int bytecount = Encoding.ASCII.GetByteCount(message.Text);
                byte[] sendData = new byte[bytecount];
                sendData = Encoding.ASCII.GetBytes(message.Text);

                NetworkStream stream = client.GetStream();
                stream.Write(sendData, 0, sendData.Length);
               
                if (client.ReceiveBufferSize > 0)
                {
                    byte[] bytes = new byte[client.ReceiveBufferSize];
                    stream.Read(bytes, 0, client.ReceiveBufferSize);// This method blocks until at least one byte is read.
                    string msg = Encoding.ASCII.GetString(bytes); //the message incoming
                    recivedServerMessage.Text = "I Recived:" + msg;
                }
                else
                {
                    recivedServerMessage.Text = "No response From Server";
                }
                ErrorMessage.Text = "Message Succsesfully sent!";

                stream.Close();
                client.Close(); // Closing the tcpClient instance does not close the network stream.
            }
            catch (Exception ex)
            {
                attempts += 1;
                ErrorMessage.Text = "Could Not Connect To Server:"+ serverIP + " On Port:"+ port + " Attemps:" + attempts;
            }


        }

        private void changeIPButton_Click(object sender, EventArgs e)
        {
            serverIP = IPTextBox.Text;
            port = Int32.Parse(PortTextBox.Text);
        }
    }
}
