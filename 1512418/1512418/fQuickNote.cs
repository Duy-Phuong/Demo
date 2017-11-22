using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _1512418
{
    public struct Tag
    {
        public string name;
        public int numberOfTag;//so note ma tag do chua
        public List<string> note;
        public string Name
        {
            get { return name; }
            set { name = value; }
        }
        public int NumberOfTag
        {
            get { return numberOfTag; }
            set { numberOfTag = value; }
        }
        public List<string> Note
        {
            get { return note; }
            set { note = value; }
        }
        public Tag(string name, int numberOfTag)
        {
            this.name = name;
            this.numberOfTag = numberOfTag;
            this.note = new List<string>();
        }
        public Tag(string name, int numberOfTag, string[] note)
        {
            this.name = name;
            this.numberOfTag = numberOfTag;
            this.note = new List<string>();
            for (int i = 0; i < note.Length; i++)
            {
                this.note[i] = note[i];
            }
        }

    }
    public partial class fQuickNote : Form
    {
        
        public fQuickNote()
        {
            Thread t = new Thread(new ThreadStart(SplashScreen));
            t.Start();
            Thread.Sleep(5000);
            InitializeComponent();

            t.Abort();
        }

        private void openQuickNoteToolStripMenuItem_Click(object sender, EventArgs e)
        {

            this.Show();
            this.WindowState = FormWindowState.Normal;//hien lai o giua nhu bt
            this.ShowInTaskbar = true;


        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }
        
        private void Form1_Move(object sender, EventArgs e)
        {
            if(this.WindowState == FormWindowState.Minimized)
            {
                this.Hide();
                notifyIcon1.Visible = true;
                //  notifyIcon1.ShowBalloonTip(1000, "Important caution!", "Add Quick note to Notification area. Click to know more...", ToolTipIcon.Info);
                this.ShowInTaskbar = false;

            }
        }

        private void notifyIcon1_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            this.Show();
            this.WindowState = FormWindowState.Normal;
            notifyIcon1.Visible = false;
            this.ShowInTaskbar = true;


        }

        private void viewNotesToolStripMenuItem_Click(object sender, EventArgs e)
        {
            fViewNote f = new fViewNote();
           // this.Hide();
            f.Show();//khi tat no ct se k tat

            //this.Show();
            //this.WindowState = FormWindowState.Normal;
            //notifyIcon1.Visible = false;
            //this.ShowInTaskbar = true;
        }

        private void viewStatitisticsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            fChart f = new fChart();
           // this.Hide();
            f.Show();//khi tat no ct se k tat

            //this.Show();
            //this.WindowState = FormWindowState.Normal;
            //notifyIcon1.Visible = false;
            //this.ShowInTaskbar = true;
            
        }
        //khi load lên ta th ẩn --------------------------------------------------
        private void fQuickNote_Load(object sender, EventArgs e)
        {
            //this.Hide();
            //notifyIcon1.Visible = true;
            //notifyIcon1.ShowBalloonTip(1000, "Important caution!", "Add Quick note to Notification area. Click to know more...", ToolTipIcon.Info);
            //this.ShowInTaskbar = false;

            SetDataToCollection();
            //this.Focus();

        }

        private void SplashScreen()
        {
            Application.Run(new fLoad());
        }
        //Thêm bằng tay vào Collection các từ khóa
        private void SetDataToCollection()
        {
            string tenFile = "tag.txt";
            string t = "";
            StreamReader read = new StreamReader(tenFile);
            string z = "";//phai khoi tao
            while (!read.EndOfStream)
            {
                t = read.ReadLine();
                z += t;
            }

            string[] subTags = null;
            subTags = z.Split('\t');

            Tag[] t1 = new Tag[100];
            for (int i = 0; i < t.Length; i++)
            {
                t1[i] = new Tag("", 0);
            }
            //string[] mangTag = null;//tuong uong ti le 1:1
            //string[] mangNote = null;
            int dem = 0;
            int index1 = 0;
            List<string> mangTag = new List<string>();
            List<string> mangNote = new List<string>();
            foreach (string a in subTags)
            {
                if (dem % 2 == 0)
                {
                    mangTag.Add(a);
                    index1++;

                }
                else
                {
                    mangNote.Add(a);
                }
                dem++;

            }
            
            read.Close();
            //////
            AutoCompleteStringCollection auto1 = new AutoCompleteStringCollection();
            txbTags.AutoCompleteMode = AutoCompleteMode.Suggest;
            txbTags.AutoCompleteSource = AutoCompleteSource.CustomSource;
            //string[] arrayName ={"Tâm",
            //              "Nhã",
            //              "Sơn",
            //              "Phúc",
            //              "Huyền",
            //              "Ngân",
            //              "Tấn Huy",
            //              "Huy Tôi",
            //              "Nguyễn "
            //              };
            foreach (string name in mangTag)
            {
                auto1.Add(name);
            }

            txbTags.AutoCompleteCustomSource = auto1;
            //txbTags.AutoCompleteCustomSource.AddRange(arrayName);
        }


        public bool kiemTra(Tag[] t, string tag, string note,ref int soLuongTag)//, ref int a
        {
            int kt = 0;//kiem tra tag co chua
            int kt1 = 0;//kiem tra note co chua
            int i;
            for (i = 0; i < soLuongTag; i++)
            {
                if (t[i].name == tag)//tim tag
                {
                    kt = 1;
                    foreach (string b in t[i].note)//tim note
                    {
                        if (b == txbTitle.Text)
                        {
                            kt1 = 1;
                            break;
                        }
                    }
                    if(kt1 == 0)
                    {
                        t[i].note.Add(txbTitle.Text);
                        t[i].NumberOfTag++;
                    }
                    kt1 = 0;
                }

            }
            if (kt == 0)
            {
                i = soLuongTag;
                t[i].name = tag;
                t[i].note.Add(txbTitle.Text);
                t[i].NumberOfTag = ++t[i].NumberOfTag;
                soLuongTag++;
            }

            kt = 0;
            return false;
        }
        //save file
        public void saveFile(Tag[] t, int soLuongTag)
        {
            //ghi ra file tag
            string tenFile1 = "tag.txt";
            FileStream fs = new FileStream(tenFile1, FileMode.Append, FileAccess.Write);
            if (fs.CanWrite)
            {
                
           
           // StreamWriter writer1 = new StreamWriter(tenFile1, true);//true neu muon ghi tiep
            for (int i = 0; i < soLuongTag; i++)
            {
                    //writer1.Write(t[i].name);
                    //writer1.Write("\t");
                    byte[] buffer = Encoding.UTF8.GetBytes( t[i].name + "\t");//xuong dòng mới bắt đầu ghi tiếp \r\n nó mới hiểu xuống dòng
                    fs.Write(buffer, 0, buffer.Length);
                    foreach (string b in t[i].note)//tim note
                {
                        //writer1.Write(b);
                        //writer1.Write("\t");
                        byte[] buffer1 = Encoding.UTF8.GetBytes(b + "\t");
                        fs.Write(buffer1, 0, buffer1.Length);
                }
                    // writer1.WriteLine();
                    byte[] buffer2 = Encoding.UTF8.GetBytes("\r\n");
                    fs.Write(buffer2, 0, buffer2.Length);
                }
           // writer1.Close();
            }
            fs.Flush();
            fs.Close();
        }

        public void btnSave_Click(object sender, EventArgs e)
        {
            string tag = txbTags.Text;
            //   fViewNote frm = new fViewNote();//lay dl
            Tag[] t = new Tag[100];
            for (int i = 0; i < t.Length; i++)
            {
                t[i] = new Tag("", 0);
            }
            string[] subTags = null;
            subTags = tag.Split(',');
            ////string x = null;
            int soLuongTag = 0;
            foreach (string a in subTags)
            {
                kiemTra(t, a, txbTitle.Text,ref soLuongTag);

                // frm.listBox_form2.Items.Add(a);

                //    x += a;
                //    x += "\r\n";
            }
          
                //  frm.Show();
                //txbContent.Text = subTags[subTags.Length  - 1];


                //ghi ra file note
                string tenFile = txbTitle.Text;
            tenFile += ".txt";
            //StreamWriter writer = new StreamWriter(tenFile, false);//true neu muon ghi tiep
            //writer.WriteLine(txbContent.Text);
            //writer.Close();

            //lưu có dấu
            FileStream fs = new FileStream(tenFile, FileMode.Create, FileAccess.Write);
            if (fs.CanWrite)
            {
                byte[] buffer = Encoding.UTF8.GetBytes(txbContent.Text);
                fs.Write(buffer, 0, buffer.Length);
            }
            fs.Flush();
            fs.Close();

            saveFile(t, soLuongTag);


             //   MessageBox.Show("Lưu thành công!", "Caution", MessageBoxButtons.OK, MessageBoxIcon.Information);


            //StreamReader read = new StreamReader(tenFile);
            //txbContent.Text = read.ReadToEnd();
            //read.Close();

            //sau nay 
            //if(txbContent.Text == "")
            //{
            //    MessageBox.Show("Bạn nên nhập nội dung cho Note", "Caution", MessageBoxButtons.OK, MessageBoxIcon.Question);
            //}

            //if (txbTags.Text == "")
            //{
            //    MessageBox.Show("Bạn nên nhập nội dung cho tag", "Caution", MessageBoxButtons.OK, MessageBoxIcon.Question);
            //}
            //txbContent.Text = "";
            // txbContent.Clear();
            // txbTags.Text = "";
        }

        private void txbTags_TextChanged(object sender, EventArgs e)
        {
        }

        private void fQuickNote_KeyDown(object sender, KeyEventArgs e)
        {
            if(e.Control && e.KeyCode == Keys.H)
            {
                //key preview == true do form có nhiều contrl nên focus đặc vào các control đó
                //    MessageBox.Show("Bạn nên nhập nội dung cho Note", "Caution", MessageBoxButtons.OK, MessageBoxIcon.Question);
                this.Hide();
                notifyIcon1.Visible = true;
                //  notifyIcon1.ShowBalloonTip(1000, "Important caution!", "Add Quick note to Notification area. Click to know more...", ToolTipIcon.Info);
                this.ShowInTaskbar = false;
            }

            //if (e.Control && e.KeyCode == Keys.L)
            //{
            //    //key preview == true
            //    MessageBox.Show("Bạn nên nhập nội dung cho Note", "Caution", MessageBoxButtons.OK, MessageBoxIcon.Question);
            //    //this.Show();
            //    //this.WindowState = FormWindowState.Normal;
            //    //notifyIcon1.Visible = false;
            //    //this.ShowInTaskbar = true;
            //}


        }

        private void txbTags_KeyDown(object sender, KeyEventArgs e)
        {

            //if (e.KeyCode.ToString() == "Oemcomma")
            //{
               
            //    txbTags.Text += ",";
            //    SetDataToCollection();
            //    //  MessageBox.Show("ban an " + e.KeyCode.ToString());


            //}
        }
    }
}
