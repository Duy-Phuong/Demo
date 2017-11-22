using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _1512418
{
    public partial class fViewNote : Form
    {
        public fViewNote()
        {
            InitializeComponent();

            lvTags.View = View.Details;
            lvTags.FullRowSelect = true;

            //construct tags
            lvTags.Columns.Add("TAGS", 140);
            lvTags.Columns.Add("NUMBER OF NOTES", 120);

            lvContent.View = View.Details;
            lvContent.FullRowSelect = true;
            //construct tags
            lvContent.Columns.Add("FILE NAME", 140);
            lvContent.Columns.Add("CONTENT BRIEF", 200);

            //lbView.Items.Add("a");
            //lbView.SelectedItem = "a";
            //txbView.Text = "ban chon ";
            //txbView.Text += lbView.SelectedItem.ToString();
        }
        //add to listview tags
        private void AddTag(string name, string num)
        {
            string[] row = { name, num };
            ListViewItem item = new ListViewItem(row);
            lvTags.Items.Add(item);
        }

        //add to listview content
        private void AddContent(string name, string num)
        {
            string[] row = { name, num };
            ListViewItem item = new ListViewItem(row);
            lvContent.Items.Add(item);
        }
        public bool kiemTra(Tag[] t, string tag, string note, ref int soLuongTag)//, ref int a
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
                        if (b == note)
                        {
                            kt1 = 1;
                            break;
                        }
                    }
                    if (kt1 == 0)
                    {
                        t[i].note.Add(note);
                        t[i].NumberOfTag++;
                    }
                    kt1 = 0;
                }

            }
            if (kt == 0)
            {
                i = soLuongTag;
                t[i].name = tag;
                t[i].Note.Add(note);
               

                t[i].NumberOfTag = ++t[i].NumberOfTag;
                soLuongTag++;
            }

            kt = 0;
            return false;
        }

        ///--------------------------------khi load lên-------------------------------------------
        private void fViewNote_Load(object sender, EventArgs e)
        {
            string tenFile = "tag.txt";
            string t = "";
            StreamReader read = new StreamReader(tenFile);
            string z= "";//phai khoi tao
            while(!read.EndOfStream)
            {
                t = read.ReadLine();
                z += t;
            }

            string[] subTags = null;
            subTags = z.Split('\t');
            string x = null;

            Tag[] t1 = new Tag[100];
            for (int i = 0; i < t1.Length; i++)//t
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
                //if(a == "")
                //{
                //    break;
                //}
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

            //foreach(string a in mangNote)
            //{

            //    x += a;
            //    x += "\r\n";
            //}
            int soLuongTag = 0;
            for (int i = 0; i < index1 - 1; i++)//tru 1 vi lan cuoi no +1
            {
                kiemTra(t1, mangTag[i], mangNote[i], ref soLuongTag);//dua vao dinh dang:  tag note1 note 2....
            }
            //in ra xem thu
            for (int i = 0; i < soLuongTag; i++)
            {
                x += t1[i].Name;
                x += "\t";
                x += t1[i].NumberOfTag;
                x += "\t";
                foreach (string b in t1[i].note)//tim note
                {
                    x += b;
                    x += "\t";
                }

                x += "\r\n";

            }

            //them vao listview
            for(int i=0; i< soLuongTag; i++)
            {
                AddTag(t1[i].Name, t1[i].NumberOfTag.ToString());
            }
           // txbView.Text = x;

            read.Close();
        }
        //khi click vao tag
        private void lvTags_MouseClick(object sender, MouseEventArgs e)
        {
            //truoc khi in lai clear het
            lvContent.Items.Clear();

            //doc file
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
            string x = null;

            Tag[] t1 = new Tag[100];
            for (int i = 0; i < t1.Length; i++)
            {
                t1[i] = new Tag("", 0);
            }
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
            
            int soLuongTag = 0;
            for (int i = 0; i < index1 - 1; i++)//tru 1 vi lan cuoi no +1
            {
                kiemTra(t1, mangTag[i], mangNote[i], ref soLuongTag);//dua vao dinh dang:  tag note1 note 2....
            }
            //in ra xem thu
            string clickTag = lvTags.SelectedItems[0].SubItems[0].Text;
            for (int i = 0; i < soLuongTag; i++)
            {
                if(clickTag == t1[i].Name)
                {
                    foreach (string b in t1[i].note)//tim note
                    {
                        string content = "";
                        string contentBrief = "";
                        x = b;
                        x += ".txt";
                        StreamReader read1 = new StreamReader(x);
                        content = read1.ReadToEnd();
                        read1.Close();
                        if(content.Length  > 50) //neu lớn hơn 50 kí tự mới lấy kí tự đầu
                        {
                            contentBrief = content.Substring(0, 50);

                        }
                        else
                        {
                            contentBrief = content;

                        }
                        AddContent(b, contentBrief);
                    }
                }
               
            }
            read.Close();
                ///--------------
              //  txbView.Text = lvTags.SelectedItems[0].SubItems[0].Text;
        }
        //khi click vao content
        private void lvContent_MouseClick(object sender, MouseEventArgs e)
        {
            string content = "";
            string ten = lvContent.SelectedItems[0].SubItems[0].Text;
            ten += ".txt";
            StreamReader read1 = new StreamReader(ten);
            content = read1.ReadToEnd();
            read1.Close();
            txbView.Text = content;
        }

        private void fViewNote_FormClosing(object sender, FormClosingEventArgs e)
        {
        }

        //public ListBox listBox_form2//lay dl tu form khac
        //{
        //    get
        //    {
        //        return lbView;
        //    }
        //    set
        //    {
        //        lbView = value;
        //    }
        //}



    }
}
