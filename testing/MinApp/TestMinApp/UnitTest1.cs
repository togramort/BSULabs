using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using MinApp;

namespace TestMinApp
{
    [TestClass]
    public class UnitTest1
    {
        private TestContext testContextInstance;

        /// <summary>
        ///Gets or sets the test context which provide
        ///information about and functionality for the current test run.
        ///</summary>
        
        public TestContext TestContext
        {
            get
            {
                return testContextInstance;
            }
            set
            {
                testContextInstance = value;
            }
        }

        [TestMethod]
        public void TestMin()
        {
            int min;
            min = Program.Min(3, 4, 5);
            Assert.AreEqual(3, min);
        }
    }
}