using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using ActiveXCPP2Lib;            //не забудьте добавить строки подключения
using AxActiveXCPP2Lib;


namespace WindowsFormsApp2
{
    public partial class Form1 : Form
    {
        static int k = 10;

        public Form1()
        {
            InitializeComponent();
            
        }
        private void Form1_Load(object sender, EventArgs e)
        {

        }
        private void axActiveXCPP21_EventHandlerTest(object sender, _DActiveXCPP2Events_EventHandlerTestEvent e)
        {
            int age = e.age;
            string name = e.name;
            string surname = e.surname;

        }
        private void button1_Click(object sender, EventArgs e)
        {

            k = axActiveXCPP21.TestMyMethod(Convert.ToInt32(textBox1.Text));
            axActiveXCPP21.EventHandlerTest +=
              new AxActiveXCPP2Lib._DActiveXCPP2Events_EventHandlerTestEventHandler(
              axActiveXCPP21_EventHandlerTest);

            textBox2.Text = k.ToString();
            //MessageBox.Show("Active returned:" + k);
        }


    }
}
