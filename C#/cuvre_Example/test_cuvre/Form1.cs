using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace test_cuvre
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            
            InitializeComponent();
            pictureBox1.MouseDoubleClick += pictureBox1_MouseMove;
            this.MouseDoubleClick += Form_MouseMove;
            DrawCurve(curvebuf);
            
        }
        
        private Point mouseOffset;
        int times = 10;//每10s采集一次数据
        int drawflag = 1;
        private int height = 350;
        private int width = 800;
        private Bitmap bitmap;
        private Graphics graphics;
        private float Tension = 0.5f;
        
        //
        //要画曲线的点y坐标值,x值为10s采集一次数据
        private float[] curvebuf = new float[] { 20.0f, 30.0f, 40.0f, 35.4f, 21.6f, 32.8f, 5.2f, 9.9f, 30f, 35.3f, 25.3f, 21.2f, 30.2f, 22.8f, 40.5f, 5.6f, 20.6f };
        private void DrawCurve(float[] buf)
        {
            //创建位图  曲线图显示的区域
            bitmap = new Bitmap(297, 250);
            //创建Graphics类对象
            graphics = Graphics.FromImage(bitmap);
            //清空图片背景色
            //graphics.Clear(Color.White);
            Font font = new System.Drawing.Font("Arial", 9, FontStyle.Regular);
            //填充背景
            //参数1：显示区域背景颜色；参数2：左边开始填充的位置，上边开始填充的位置；参数3：右边填充结束位置，参数4：下边填充结束的位置。
            graphics.FillRectangle(Brushes.Black, 23, 25, 274, 225);
            Brush brush1 = new SolidBrush(Color.Blue);
            Brush brush2 = new SolidBrush(Color.SaddleBrown);
            Brush brushPoint = new SolidBrush(Color.Red);
            //画图片的边框线
            Pen mypenBlack = new Pen(Color.Black, 1);//绘制的矩形框颜色
            graphics.DrawRectangle(mypenBlack, 23, 25, 274, 274);//矩形
            //graphics.DrawRectangle(mypenBlack, 40, 35, 720, 720); //矩形


            Pen mypenBlue = new Pen(Color.Blue, 1);//线条
            Pen mypenRed = new Pen(Color.Red, 1);
            Pen mypenYellow = new Pen(Color.Yellow, 1);//点颜色
            //绘制线条
            //绘制纵向线条
            int x = 80;
            //参数1:绘制线条的颜色，参数2：起点x轴位置，参数3：起点y轴位置；参数4：终点x轴位置，参数5：终点y轴位置
            //graphics.DrawLine(new Pen(Color.Red, 5), 23, 0, 23, 274);
            for (int i = 0; i < 17; i++)
            {
                graphics.DrawLine(mypenBlue, x, 40, x, 310);
                x = x + 40;
            }

            //绘制横向线条
            int y = 70;
            for (int i = 0; i < 8; i++)
            {
                graphics.DrawLine(mypenBlue, 40, y, 760, y);
                y = y + 30;
            }

            //x轴上对应的标记
            String[] n = { " 10", " 20", " 30", " 40", " 50", " 60", " 70",
               " 80", " 90", " 100", "110", "120", "130", "140", "150", "160", "170"};
            x = 70;
            for (int i = 0; i < 17; i++)
            {
                graphics.DrawString(n[i].ToString(), font, Brushes.Red, x, 315); //设置文字内容及输出位置

                x = x + 40;
            }

            //y轴上对应的标记
            String[] m = { "40", "35", "30", "25", "20", "15", "10", " 5" };
            y = 60;
            for (int i = 0; i < 8; i++)
            {
                graphics.DrawString(m[i].ToString(), font, Brushes.Red, 16, y); //设置文字内容及输出位置
                y = y + 30;
            }
            //画曲线
            if (drawflag == 1)
            {
                int len = buf.Length;
                PointF[] CurvePointF = new PointF[len];//坐标点

                float pointX = 0;
                float pointY = 0;
                for (int i = 0; i < 2; i++)
                {
                    pointX = i * times * 4 + 80;    //坐标系（0，0）实际位置为（70,310）实际工程坐标左上角为原点。
                    pointY = 310 - 60 * (buf[i] / 10);
                    CurvePointF[i] = new PointF(pointX, pointY);

                    graphics.FillEllipse(brushPoint, pointX - 4, pointY - 4, 8, 8);//画点，是以圆心为切点画的圆，所以减去半径
                
                }
                graphics.DrawCurve(mypenYellow, CurvePointF, Tension);//画曲线

                label2.Text = Convert.ToString("输出点个数：" + len);
            }

            graphics.Dispose();
            this.pictureBox1.Image = bitmap;

        }
        
        private void Form_MouseMove(object sender, MouseEventArgs e)
        {
            Console.WriteLine("调用");
            mouseOffset.X = (e.X - 40) / 4;
            mouseOffset.Y = (310 - e.Y) / 6;
            int ex = e.X;
            int ey = e.Y;
            label1.Visible = true;
            label1.Text = ("坐标值：" + "\n" + "x=" + mouseOffset.X + "\n" + "y=" + mouseOffset.Y);
            label1.Location = new Point(ex + 20, ey + 10);
        }
        
        private void pictureBox1_MouseMove(object sender, MouseEventArgs e)
        {
            int ex = e.X;
            int ey = e.Y;

            mouseOffset.X = (e.X - 40) / 4;
            mouseOffset.Y = (310 - e.Y) / 6;
            if ((ex > 40 && ex < 760) && (ey > 40 && ey < 310))
            {
                label1.BackColor = Color.FromArgb(80, Color.White);

                label1.Visible = true;
                label1.Text = ("坐标值：" + "\n" + "x=" + mouseOffset.X + "\n" + "y=" + mouseOffset.Y);
                label1.Location = new Point(ex + 20, ey + 10);
            }
            else
            {
                label1.Visible = false;
            }
        }         

        private void Draw_Click(object sender, EventArgs e)
        {
            int lens = curvebuf.Length;
            if (lens <= 1)
            {
                drawflag = 0;
                MessageBox.Show("数据小于2！", "错误",
                          MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }
            else
            {
                drawflag = 1;
                DrawCurve(curvebuf);
            }
        }

        private void clean_btn_Click(object sender, EventArgs e)
        {
            drawflag = 0;
            label2.Text = Convert.ToString("输出点个数：");
            DrawCurve(curvebuf);
        }

        private void custom_draw_btn_Click(object sender, EventArgs e)
        {
            label1.Visible = false;
            label1.Parent = pictureBox1;
            DrawCurve(curvebuf);

        }
        private void custom_draw_btn_Click1(object sender, EventArgs e)
        {
            label1.Visible = false;
            label1.Parent = pictureBox1;
            DrawCurve(curvebuf);

        }
    }
}
