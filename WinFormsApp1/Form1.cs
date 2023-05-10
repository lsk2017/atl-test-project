using testcomLib;

namespace WinFormsApp1
{
    public partial class Form1 : Form
    {
        FastCom fc = null;
        public Form1()
        {
            InitializeComponent();

            fc = new testcomLib.FastCom();
            var ret = fc.Sum(1, 1);
            Console.WriteLine(ret);

            label1.Text = ret.ToString();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }
    }
}