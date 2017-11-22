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
    public partial class fChart : Form
    {
        public fChart()
        {
            InitializeComponent();

           
           
        }

        private void fChart_Load(object sender, EventArgs e)
        {
            //SolidBrush sb = new SolidBrush(Color.Red);
            //Graphics g = this.CreateGraphics();
            //g.FillRectangle(sb, 0, 0, 50, 50);
            //sb.Dispose();
            //g.Dispose();
            //DrawChart();
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
                t[i].note.Add(note);
                t[i].NumberOfTag = ++t[i].NumberOfTag;
                soLuongTag++;
            }

            kt = 0;
            return false;
        }
        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);

            Graphics g = e.Graphics;
            //load tu dong
            //using (Pen selPen = new Pen(Color.Blue))
            //{
            //    g.DrawRectangle(selPen, 10, 10, 50, 50);
            //}

            DrawChart(g);
        }
        public void DrawChart(Graphics g)
        {
            List<SolidBrush> cha = new List<SolidBrush>();
            cha.Add(new SolidBrush(Color.Red));
            cha.Add(new SolidBrush(Color.Orange));
            cha.Add(new SolidBrush(Color.Yellow));
            cha.Add(new SolidBrush(Color.GreenYellow));
            cha.Add(new SolidBrush(Color.Aquamarine));

            cha.Add(new SolidBrush(Color.Violet));
            cha.Add(new SolidBrush(Color.Green));
            cha.Add(new SolidBrush(Color.Blue));
            cha.Add(new SolidBrush(Color.OrangeRed));
            cha.Add(new SolidBrush(Color.LightGray));

            cha.Add(new SolidBrush(Color.BlueViolet));
            cha.Add(new SolidBrush(Color.Aqua));
            cha.Add(new SolidBrush(Color.Aquamarine));
            cha.Add(new SolidBrush(Color.Azure));
            cha.Add(new SolidBrush(Color.AliceBlue));



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
            // string x = null;

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
            //vẽ
            int sum = 0;//so note tong cong
            int sumOtherTag = 0;//so note khi nó lớn hơn 10
            for (int i = 0; i < soLuongTag; i++)
            {
                sum += t1[i].NumberOfTag;
                if (i > 10)
                {
                    sumOtherTag += t1[i].NumberOfTag;
                }
            }
            float pos = 270;
            float x1 = 0.0f;
            float t11 = 0.0f;
            int vty = 50;
            g = this.CreateGraphics();
            List<float> phanTram = new List<float>();
            for (int i = 0; i < soLuongTag; i++)
            {
                x1 = (float)(360.0f * ((t1[i].NumberOfTag * 100.0f) / sum) / 100.0f);
                if (i == (soLuongTag - 1) || i == 11)
                {
                    x1 = 360 - t11;
                }
                g.FillPie(cha[i], 80, 50, 200, 200, pos, x1);
                pos += x1;
                t11 += x1;//de tinh cai cuoi

                if (pos > 360)
                    pos -= 360;
                x1 = (float)(t1[i].NumberOfTag * 100.0f) / sum; //tinh xuat ra tong so vơi 100%
                if(i == 11)//neu th những tag khác
                {
                    x1 = (float)(sumOtherTag * 100.0f) / sum; //tinh xuat ra tong so vơi 100%

                }
                phanTram.Add(x1);
                //bang chu thich
                g.FillRectangle(cha[i], 400, vty, 50, 25);
                vty += 30;
                if (i == 11)
                    break;
            }
            ////----------------------------------chú thích--------------------------------------
            string tenBD = "Biểu đồ dựa vào số tag và số note liên quan tới tag";
            tenBD += "\n              có " + soLuongTag.ToString() + " Tags ";
            tenBD += "và có " + sum.ToString() + " Notes\n";
            label1.Text = tenBD;
            vty = 50;
            Label[] lbl = new Label[15];// khai bao mang gom 10 Label.
            for (int i = 0; i < soLuongTag; i++)
            {
                if (i == 12)//chu thich nhung tag khac
                {
                    break;
                }
                lbl[i] = new Label();
                if (i < 11)
                {
                    lbl[i].Name = "- " + t1[i].Name;
                    lbl[i].Text = "- " + t1[i].Name + " chứa " + t1[i].NumberOfTag.ToString() + " Note" + " (" + phanTram[i].ToString() + " %)";
                }
                else
                {
                    lbl[i].Name = "- Others tag";
                    lbl[i].Text = "- Others tag" + " chứa " + sumOtherTag.ToString() + " Note" + " (" + phanTram[i].ToString() + " %)";
                }

                lbl[i].Location = new System.Drawing.Point(455, vty); // vi tri xuat hien
                lbl[i].Size = new System.Drawing.Size(350, 25);  // kich thuoc
                lbl[i].Font = new System.Drawing.Font("Times New Roman", 12F);
                this.Controls.Add(lbl[i]);// them controls vaof Form1
                vty += 30;
              
            }

            //int pos = 270;
            //SolidBrush sb = new SolidBrush(Color.Aquamarine);
            //Graphics g = this.CreateGraphics();
            //// g.FillRectangle(sb, 0, 0, 50, 50);
            //int x = 10;
            //for(int i = 0; i < 14; i++)
            //{
            //    g.FillPie(cha[i], x, x, 20, 20, 270, 360);
            //    x += 25;

            //}
            //sb.Dispose();
            //g.Dispose();
            read.Close();

        }
        private void fChart_Click(object sender, EventArgs e)
        {
            List<SolidBrush> cha = new List<SolidBrush>();
            cha.Add(new SolidBrush(Color.Red));
            cha.Add(new SolidBrush(Color.Orange));
            cha.Add(new SolidBrush(Color.Yellow));
            cha.Add(new SolidBrush(Color.GreenYellow));
            cha.Add(new SolidBrush(Color.Aquamarine));

            cha.Add(new SolidBrush(Color.Violet));
            cha.Add(new SolidBrush(Color.Green));
            cha.Add(new SolidBrush(Color.Blue));
            cha.Add(new SolidBrush(Color.OrangeRed));
            cha.Add(new SolidBrush(Color.LightGray));

            cha.Add(new SolidBrush(Color.BlueViolet));
            cha.Add(new SolidBrush(Color.Aqua));
            cha.Add(new SolidBrush(Color.Aquamarine));
            cha.Add(new SolidBrush(Color.Azure));
            cha.Add(new SolidBrush(Color.AliceBlue));



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
           // string x = null;

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
            //vẽ
            List<float> phanTram = new List<float>();

            int sum = 0;//so note tong cong
            int sumOtherTag = 0;//so note khi nó lớn hơn 10
            for (int i=0; i< soLuongTag; i++)
            {
                sum += t1[i].NumberOfTag;
              if(i > 10)
                {
                    sumOtherTag += t1[i].NumberOfTag;
                }
            }
            float pos = 270;
            float x1 = 0.0f;
            float t11 = 0.0f;
            int vty = 50;
            Graphics g = this.CreateGraphics();
            for (int i = 0; i < soLuongTag; i++)
            {
                x1 = (float)(360.0f * ((t1[i].NumberOfTag * 100.0f) / sum) / 100.0f);
                if (i == (soLuongTag - 1) || i == 11)//la dua cuoi hay qua nhung tag khac
                {
                    x1 = 360 - t11;
                }
                
                g.FillPie(cha[i], 80, 50, 200, 200, pos, x1);
                pos += x1;
                t11 += x1;//de tinh cai cuoi

                if (pos > 360)
                    pos -= 360;
                x1 = (float)(t1[i].NumberOfTag * 100.0f) / sum;
                if (i == 11)//neu th những tag khác
                {
                    x1 = (float)(sumOtherTag * 100.0f) / sum; //tinh xuat ra tong so vơi 100%

                }
                phanTram.Add(x1);
                //bang chu thich
                g.FillRectangle(cha[i], 400, vty, 50, 25);
                vty += 30;
                if (i == 11)//thoat
                {
                    break;
                }
            }
            ////----------------------------------chú thích--------------------------------------
            string tenBD = "Biểu đồ dựa vào số tag và số note liên quan tới tag";
            tenBD += "\n              có " + soLuongTag.ToString() + " Tags ";
            tenBD += "và có " + sum.ToString() + " Notes\n";
            label1.Text = tenBD;
            //label2.Text = "Chú thích Tag";
            vty = 50;
            Label[] lbl = new Label[15];// khai bao mang gom 15 Label.
            for (int i = 0; i < soLuongTag; i++)
            {
                lbl[i] = new Label();
                if (i < 11)
                {
                    lbl[i].Name = "- " + t1[i].Name;
                    lbl[i].Text = "- " + t1[i].Name + " chứa " + t1[i].NumberOfTag.ToString() + " Note" + " (" + phanTram[i].ToString() + " %)";
                }
                else
                {
                    lbl[i].Name = "- Others tag";
                    lbl[i].Text = "- Others tag" + " chứa " + sumOtherTag.ToString() + " Note" + " (" + phanTram[i].ToString() + " %)";
                }
                
                lbl[i].Location = new System.Drawing.Point(455, vty); // vi tri xuat hien
                lbl[i].Size = new System.Drawing.Size(350, 25);  // kich thuoc
                lbl[i].Font = new System.Drawing.Font("Times New Roman", 12F);
                this.Controls.Add(lbl[i]);// them controls vaof Form1
                vty += 30;
                if(i==11)//chu thich nhung tag khac
                {
                    break;
                }
            }

            //int pos = 270;
            //SolidBrush sb = new SolidBrush(Color.Aquamarine);
            //Graphics g = this.CreateGraphics();
            //// g.FillRectangle(sb, 0, 0, 50, 50);
            //int x = 10;
            //for(int i = 0; i < 14; i++)
            //{
            //    g.FillPie(cha[i], x, x, 20, 20, 270, 360);
            //    x += 25;

            //}
            //sb.Dispose();
            //g.Dispose();
            read.Close();

        }
    }
}
