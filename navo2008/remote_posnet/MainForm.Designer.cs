namespace navo2012.remote_posnet
{
    partial class MainForm
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
            this.components = new System.ComponentModel.Container();
            this.messages_list = new System.Windows.Forms.ListBox();
            this.Timer = new System.Windows.Forms.Timer(this.components);
            this.SuspendLayout();
            // 
            // messages_list
            // 
            this.messages_list.FormattingEnabled = true;
            this.messages_list.Location = new System.Drawing.Point(12, 12);
            this.messages_list.Name = "messages_list";
            this.messages_list.Size = new System.Drawing.Size(657, 355);
            this.messages_list.TabIndex = 0;
            // 
            // Timer
            // 
            this.Timer.Interval = 2000;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.RoyalBlue;
            this.ClientSize = new System.Drawing.Size(681, 380);
            this.Controls.Add(this.messages_list);
            this.Name = "MainForm";
            this.Text = "NAVO2012 Remote Posnet Printer 1.7";
            this.WindowState = System.Windows.Forms.FormWindowState.Minimized;
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MainForm_FormClosing);
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ListBox messages_list;
        private System.Windows.Forms.Timer Timer;
    }
}

