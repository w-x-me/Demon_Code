using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace test_cuvre
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            
            InitializeComponent();
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.SizableToolWindow;
            pictureBox1.MouseDoubleClick += pictureBox1_MouseMove;
            this.MouseDoubleClick += Form_MouseMove;
            DrawCurve(curvebuf);
            this.pictureBox1.SizeMode=PictureBoxSizeMode.StretchImage
            
        }
        [DllImport("kernel32")]
        private static extern int GetPrivateProfileInt(string lpAppName, string lpKeyName, int nDefault, string lpFileName);
        
        private Point mouseOffset;
        int move_pixe1 = 25;//每次采集一次数据，x轴移动多少
        int y_vaule = 10;//Y轴原点坐标值（按照后面等分情况，判断原点第一个值数据值）
        int drawflag = 1;
        private Bitmap bitmap;
        private Graphics graphics;
        private float Tension = 0.5f;
        
        //
        //要画曲线的点y坐标值,x值为10s采集一次数据
        private int[] curvebuf = new int[] { 20, 25, 26, 27, 18, 17, 12, 10, 15, 25};
        private void DrawCurve(int[] buf)
        {
            int x_value, x_wheelbase, y_value, y_wheelbase;

            x_value = GetPrivateProfileInt("x_value", "x", 5, "D:/work/C#/Battery_Pressure_cuvre/test_cuvre/config.ini");
            x_wheelbase = GetPrivateProfileInt("x_value", "x_wheelbase", 5, "D:/work/C#/Battery_Pressure_cuvre/test_cuvre/config.ini");
            y_value = GetPrivateProfileInt("x_value", "y", 30, "D:/work/C#/Battery_Pressure_cuvre/test_cuvre/config.ini");
            y_wheelbase = GetPrivateProfileInt("x_value", "y_wheelbase", 2, "D:/work/C#/Battery_Pressure_cuvre/test_cuvre/config.ini");
            //创建位图  曲线图显示的区域
            bitmap = new Bitmap(297, 250);
            //创建Graphics类对象
            graphics = Graphics.FromImage(bitmap);
            //清空图片背景色
            //graphics.Clear(Color.White);
            Font font = new System.Drawing.Font("Arial", 9, FontStyle.Regular);
            //填充背景
            //参数1：显示区域背景颜色；参数2：左边开始填充的位置，上边开始填充的位置；参数3：右边填充结束位置，参数4：下边填充结束的位置。
            graphics.FillRectangle(Brushes.Black, 0, 0, 297, 250);
            Brush brush1 = new SolidBrush(Color.Blue);
            Brush brush2 = new SolidBrush(Color.SaddleBrown);
            Brush brushPoint = new SolidBrush(Color.Red);
            //画图片的边框线
            Pen mypenBlack = new Pen(Color.Green, 1);//绘制的矩形框颜色
            //参数1:绘制线条的颜色，参数2：起点x轴位置，参数3：起点y轴位置；参数4：矩形宽度，参数5：矩形高度
            graphics.DrawRectangle(mypenBlack, 23, 25, 251, 200);//矩形

            Pen mypenBlue = new Pen(Color.Green, 1);//线条
            Pen mypenRed = new Pen(Color.Red, 1);
            Pen mypenYellow = new Pen(Color.Yellow, 1);//点颜色
            //绘制线条
            //绘制纵向线条
            int x = 23;
            //参数1：线条颜色，参数2：起点x轴位置，参数3：起点y轴位置，参数4：终点x轴位置，参数5：终点y轴位置
            graphics.DrawLine(new Pen(Color.Green, 3), 23, 5, 23, 226);
            for (int i = 0; i < 10; i++)
            {
                graphics.DrawLine(mypenBlue, x, 25, x, 225);
                x = x + 25;
            }
            
            //绘制横向线条
            int y = 25;
            graphics.DrawLine(new Pen(Color.Green, 3), 23, 226, 290, 226);
            for (int i = 0; i < 10; i++)
            {
                graphics.DrawLine(mypenBlue, 23, y, 274, y);
                y = y + 20;
            }
            //
            ////x轴上对应的标记
            graphics.DrawString("0", font, Brushes.Red, 16, 230);
            x = 40;
            for (int i = 0; i < 10; i++)
            {
                graphics.DrawString(x_value.ToString(), font, Brushes.Red, x, 230); //设置文字内容及输出位置
                x_value += x_wheelbase;
                x = x +25;
            }
            //
            ////y轴上对应的标记
            int[] m = { 30, 28, 26, 24, 22, 20, 18, 16, 14, 12 };
            y = 20;
            for (int i = 0; i < 10; i++)
            {
                graphics.DrawString(y_value.ToString(), font, Brushes.Red, 4, y); //设置文字内容及输出位置
                y = y + 20;
                y_value -= y_wheelbase;
            }
            //画曲线
            if (drawflag == 1)
            {
                int len = buf.Length;
                PointF[] CurvePointF = new PointF[10];//坐标点
            
                float pointX = 0;
                float pointY = 0;
                for (int i = 0; i < 10; i++)
                {
                    pointX = i * move_pixe1 + 23;    //坐标系（0，0）实际位置为（70,310）实际工程坐标左上角为原点。
                    pointY = 205 - 10 * (buf[i] - y_vaule);
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
