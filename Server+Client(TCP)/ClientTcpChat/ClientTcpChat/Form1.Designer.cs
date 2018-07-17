namespace ClientTcpChat
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.message = new System.Windows.Forms.TextBox();
            this.submit = new System.Windows.Forms.Button();
            this.ErrorMessage = new System.Windows.Forms.Label();
            this.Iplable = new System.Windows.Forms.Label();
            this.portLable = new System.Windows.Forms.Label();
            this.IPTextBox = new System.Windows.Forms.TextBox();
            this.PortTextBox = new System.Windows.Forms.TextBox();
            this.changeIPButton = new System.Windows.Forms.Button();
            this.recivedServerMessage = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // message
            // 
            this.message.Location = new System.Drawing.Point(63, 93);
            this.message.Name = "message";
            this.message.Size = new System.Drawing.Size(424, 20);
            this.message.TabIndex = 0;
            // 
            // submit
            // 
            this.submit.Location = new System.Drawing.Point(211, 194);
            this.submit.Name = "submit";
            this.submit.Size = new System.Drawing.Size(87, 29);
            this.submit.TabIndex = 1;
            this.submit.Text = "Submit";
            this.submit.UseVisualStyleBackColor = true;
            this.submit.Click += new System.EventHandler(this.button1_Click);
            // 
            // ErrorMessage
            // 
            this.ErrorMessage.AutoSize = true;
            this.ErrorMessage.Location = new System.Drawing.Point(181, 9);
            this.ErrorMessage.Name = "ErrorMessage";
            this.ErrorMessage.Size = new System.Drawing.Size(135, 13);
            this.ErrorMessage.TabIndex = 2;
            this.ErrorMessage.Text = "Send SomeThing to Server";
            // 
            // Iplable
            // 
            this.Iplable.AutoSize = true;
            this.Iplable.Location = new System.Drawing.Point(337, 140);
            this.Iplable.Name = "Iplable";
            this.Iplable.Size = new System.Drawing.Size(17, 13);
            this.Iplable.TabIndex = 3;
            this.Iplable.Text = "IP";
            // 
            // portLable
            // 
            this.portLable.AutoSize = true;
            this.portLable.Location = new System.Drawing.Point(337, 167);
            this.portLable.Name = "portLable";
            this.portLable.Size = new System.Drawing.Size(26, 13);
            this.portLable.TabIndex = 4;
            this.portLable.Text = "Port";
            // 
            // IPTextBox
            // 
            this.IPTextBox.Location = new System.Drawing.Point(378, 133);
            this.IPTextBox.Name = "IPTextBox";
            this.IPTextBox.Size = new System.Drawing.Size(109, 20);
            this.IPTextBox.TabIndex = 5;
            // 
            // PortTextBox
            // 
            this.PortTextBox.Location = new System.Drawing.Point(378, 160);
            this.PortTextBox.Name = "PortTextBox";
            this.PortTextBox.Size = new System.Drawing.Size(109, 20);
            this.PortTextBox.TabIndex = 6;
            // 
            // changeIPButton
            // 
            this.changeIPButton.Location = new System.Drawing.Point(378, 195);
            this.changeIPButton.Name = "changeIPButton";
            this.changeIPButton.Size = new System.Drawing.Size(108, 27);
            this.changeIPButton.TabIndex = 7;
            this.changeIPButton.Text = "Change IP/Port";
            this.changeIPButton.UseVisualStyleBackColor = true;
            this.changeIPButton.Click += new System.EventHandler(this.changeIPButton_Click);
            // 
            // recivedServerMessage
            // 
            this.recivedServerMessage.AutoSize = true;
            this.recivedServerMessage.Location = new System.Drawing.Point(158, 275);
            this.recivedServerMessage.Name = "recivedServerMessage";
            this.recivedServerMessage.Size = new System.Drawing.Size(144, 13);
            this.recivedServerMessage.TabIndex = 8;
            this.recivedServerMessage.Text = "TheServerSentMeAMessage";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(563, 337);
            this.Controls.Add(this.recivedServerMessage);
            this.Controls.Add(this.changeIPButton);
            this.Controls.Add(this.PortTextBox);
            this.Controls.Add(this.IPTextBox);
            this.Controls.Add(this.portLable);
            this.Controls.Add(this.Iplable);
            this.Controls.Add(this.ErrorMessage);
            this.Controls.Add(this.submit);
            this.Controls.Add(this.message);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox message;
        private System.Windows.Forms.Button submit;
        private System.Windows.Forms.Label ErrorMessage;
        private System.Windows.Forms.Label Iplable;
        private System.Windows.Forms.Label portLable;
        private System.Windows.Forms.TextBox IPTextBox;
        private System.Windows.Forms.TextBox PortTextBox;
        private System.Windows.Forms.Button changeIPButton;
        private System.Windows.Forms.Label recivedServerMessage;
    }
}

