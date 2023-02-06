//////////////////////////////////////////////////////////////////////////////////////////////////
// File Name: TspForm.cs
//      Date: 06/01/2006
// Copyright (c) 2006 Michael LaLena. All rights reserved.  (www.lalena.com)
// Permission to use, copy, modify, and distribute this Program and its documentation,
//  if any, for any purpose and without fee is hereby granted, provided that:
//   (i) you not charge any fee for the Program, and the Program not be incorporated
//       by you in any software or code for which compensation is expected or received;
//   (ii) the copyright notice listed above appears in all copies;
//   (iii) both the copyright notice and this Agreement appear in all supporting documentation; and
//   (iv) the name of Michael LaLena or lalena.com not be used in advertising or publicity
//          pertaining to distribution of the Program without specific, written prior permission. 
///////////////////////////////////////////////////////////////////////////////////////////////////
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.IO;
using System.Globalization;

namespace Tsp
{
    /// <summary>
    /// Main form for the Travelling Salesman Problem
    /// </summary>
    public partial class TspForm : Form
    {
        /// <summary>
        /// The list of cities where we are trying to find the best tour.
        /// </summary>
        Cities cityList = new Cities();

        /// <summary>
        /// The class that does all the work in the TSP algorithm.
        /// If this is not null, then the algorithm is still running.
        /// </summary>
        Tsp tsp;

        /// <summary>
        /// The image that we draw the tour on.
        /// </summary>
        Image cityImage;

        /// <summary>
        /// The graphics object for the image that we draw the tour on.
        /// </summary>
        Graphics cityGraphics;

        /// <summary>
        /// Delegate for the thread that runs the TSP algorithm.
        /// We use a separate thread so the GUI can redraw as the algorithm runs.
        /// </summary>
        /// <param name="sender">Object that generated this event.</param>
        /// <param name="e">Event arguments.</param>
        public delegate void DrawEventHandler(Object sender, TspEventArgs e);

        /// <summary>
        /// Default constructor.
        /// </summary>
        public TspForm()
        {
            InitializeComponent();
        }

        /// <summary>
        /// TSP algorithm raised an event that a new best tour was found.
        /// We need to do an invoke on the GUI thread before doing any draw code.
        /// </summary>
        /// <param name="sender">Object that generated this event.</param>
        /// <param name="e">Event arguments.</param>
        private void tsp_foundNewBestTour(object sender, TspEventArgs e)
        {
            if ( this.InvokeRequired )
            {
                try
                {
                    this.Invoke(new DrawEventHandler(DrawTour), new object[] { sender, e });
                    return;
                }
                catch (Exception)
                {
                    // This will fail when run as a control in IE due to a security exception.
                }
            }

            DrawTour(sender, e);
        }

        /// <summary>
        /// A new "best" tour from the TSP algorithm has been received.
        /// Draw the tour on the form, and update a couple of status labels.
        /// </summary>
        /// <param name="sender">Object that generated this event.</param>
        /// <param name="e">Event arguments.</param>
        public void DrawTour(object sender, TspEventArgs e)
        {
            this.lastFitnessValue.Text = Math.Round(e.BestTour.Fitness, 2).ToString(CultureInfo.CurrentCulture);
            this.lastIterationValue.Text = e.Generation.ToString(CultureInfo.CurrentCulture);

            if (cityImage == null)
            {
                cityImage = new Bitmap(tourDiagram.Width, tourDiagram.Height);
                cityGraphics = Graphics.FromImage(cityImage);
            }

            int lastCity = 0;
            int nextCity = e.BestTour[0].Connection1;

            cityGraphics.FillRectangle(Brushes.White, 0, 0, cityImage.Width, cityImage.Height);
            foreach( City city in e.CityList )
            {
                // Draw a circle for the city.
                cityGraphics.DrawEllipse(Pens.Black, city.Location.X - 2, city.Location.Y - 2, 5, 5);

                // Draw the line connecting the city.
                cityGraphics.DrawLine(Pens.Black, cityList[lastCity].Location, cityList[nextCity].Location);

                // figure out if the next city in the list is [0] or [1]
                if (lastCity != e.BestTour[nextCity].Connection1)
                {
                    lastCity = nextCity;
                    nextCity = e.BestTour[nextCity].Connection1;
                }
                else
                {
                    lastCity = nextCity;
                    nextCity = e.BestTour[nextCity].Connection2;
                }
            }

            this.tourDiagram.Image = cityImage;

            if (e.Complete)
            {
                StartButton.Text = "Begin";
                StatusLabel.Text = "Open a City List or click the map to place cities.";
                StatusLabel.ForeColor = Color.Black;
            }
        }

        /// <summary>
        /// Draw just the list of cities.
        /// </summary>
        /// <param name="cityList">The list of cities to draw.</param>
        private void DrawCityList(Cities cityList)
        {
            Image cityImage = new Bitmap(tourDiagram.Width, tourDiagram.Height);
            Graphics graphics = Graphics.FromImage(cityImage);

            foreach (City city in cityList)
            {
                // Draw a circle for the city.
                graphics.DrawEllipse(Pens.Black, city.Location.X - 2, city.Location.Y - 2, 5, 5);
            }

            this.tourDiagram.Image = cityImage;

            updateCityCount();
        }

        /// <summary>
        /// User clicked the start button to start the TSP algorithm.
        /// If it is already running, then this button will say stop and we will stop the TSP.
        /// Otherwise, 
        /// </summary>
        /// <param name="sender">Object that generated this event.</param>
        /// <param name="e">Event arguments.</param>
        private void StartButton_Click(object sender, EventArgs e)
        {
            // we are already running, so tell the tsp thread to halt.
            if (tsp != null)
            {
                tsp.Halt = true;
                return;
            }

            int populationSize = 0;
            int maxGenerations = 0;
            int mutation = 0;
            int groupSize = 0;
            int numberOfCloseCities = 0;
            int chanceUseCloseCity = 0;
            int seed = 0;

            try
            {
                populationSize = Convert.ToInt32(populationSizeTextBox.Text, CultureInfo.CurrentCulture);
                maxGenerations = Convert.ToInt32(maxGenerationTextBox.Text, CultureInfo.CurrentCulture);
                mutation = Convert.ToInt32(mutationTextBox.Text, CultureInfo.CurrentCulture);
                groupSize = Convert.ToInt32(groupSizeTextBox.Text, CultureInfo.CurrentCulture);
                numberOfCloseCities = Convert.ToInt32(NumberCloseCitiesTextBox.Text, CultureInfo.CurrentCulture);
                chanceUseCloseCity = Convert.ToInt32(CloseCityOddsTextBox.Text, CultureInfo.CurrentCulture);
                seed = Convert.ToInt32(randomSeedTextBox.Text, CultureInfo.CurrentCulture);
            }
            catch (FormatException)
            {
            }

            if (populationSize <= 0)
            {
                MessageBox.Show("You must specify a Population Size", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error, MessageBoxDefaultButton.Button1 ,MessageBoxOptions.DefaultDesktopOnly);
                return;
            }
            if (maxGenerations <= 0)
            {
                MessageBox.Show("You must specify a Maximum Number of Generations", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error, MessageBoxDefaultButton.Button1, MessageBoxOptions.DefaultDesktopOnly);
                return;
            }
            if ((mutation < 0) || (mutation > 100))
            {
                MessageBox.Show("Mutation must be between 0 and 100.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error, MessageBoxDefaultButton.Button1, MessageBoxOptions.DefaultDesktopOnly);
                return;
            }
            if ((groupSize < 2) || ( groupSize > populationSize ))
            {
                MessageBox.Show("You must specify a Group (Neighborhood) Size between 2 and the population size.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error, MessageBoxDefaultButton.Button1, MessageBoxOptions.DefaultDesktopOnly);
                return;
            }
            if ((numberOfCloseCities < 3) || (numberOfCloseCities >= cityList.Count))
            {
                MessageBox.Show("The number of nearby cities to evaluate for the greedy initial populations must be more than 3 and less than the total number of cities.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error, MessageBoxDefaultButton.Button1, MessageBoxOptions.DefaultDesktopOnly);
                return;
            }
            if ((chanceUseCloseCity < 0) || (chanceUseCloseCity > 95))
            {
                MessageBox.Show("The odds of using a nearby city when creating the initial population must be between 0% - 95%.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error, MessageBoxDefaultButton.Button1, MessageBoxOptions.DefaultDesktopOnly);
                return;
            }
            if (seed < 0)
            {
                MessageBox.Show("You must specify a Seed for the Random Number Generator", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error, MessageBoxDefaultButton.Button1, MessageBoxOptions.DefaultDesktopOnly);
                return;
            }
            if (cityList.Count < 5)
            {
                MessageBox.Show("You must either load a City List file, or click the map to place at least 5 cities. ", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error, MessageBoxDefaultButton.Button1, MessageBoxOptions.DefaultDesktopOnly);
                return;
            }

            this.StartButton.Text = "Stop";
            ThreadPool.QueueUserWorkItem( new WaitCallback(BeginTsp));
        }

        /// <summary>
        /// Starts up the TSP class.
        /// This function executes on a thread pool thread.
        /// </summary>
        /// <param name="stateInfo">Not used</param>
        private void BeginTsp(Object stateInfo)
        {
            // Assume the StartButton_Click did all the error checking
            int populationSize = Convert.ToInt32(populationSizeTextBox.Text, CultureInfo.CurrentCulture);
            int maxGenerations = Convert.ToInt32(maxGenerationTextBox.Text, CultureInfo.CurrentCulture); ;
            int mutation = Convert.ToInt32(mutationTextBox.Text, CultureInfo.CurrentCulture);
            int groupSize = Convert.ToInt32(groupSizeTextBox.Text, CultureInfo.CurrentCulture);
            int seed = Convert.ToInt32(randomSeedTextBox.Text, CultureInfo.CurrentCulture);
            int numberOfCloseCities = Convert.ToInt32(NumberCloseCitiesTextBox.Text, CultureInfo.CurrentCulture);
            int chanceUseCloseCity = Convert.ToInt32(CloseCityOddsTextBox.Text, CultureInfo.CurrentCulture);

            cityList.CalculateCityDistances(numberOfCloseCities);

            tsp = new Tsp();
            tsp.foundNewBestTour += new Tsp.NewBestTourEventHandler(tsp_foundNewBestTour);
            tsp.Begin(populationSize, maxGenerations, groupSize, mutation, seed, chanceUseCloseCity, cityList);
            tsp.foundNewBestTour -= new Tsp.NewBestTourEventHandler(tsp_foundNewBestTour);
            tsp = null;
        }

        /// <summary>
        /// User is selecting a new city list XML file.
        /// Not allowed if running the TSP algorithm.
        /// </summary>
        /// <param name="sender">Object that generated this event.</param>
        /// <param name="e">Event arguments.</param>
        private void selectFileButton_Click(object sender, EventArgs e)
        {
            OpenFileDialog fileOpenDialog = new OpenFileDialog();
            fileOpenDialog.Filter = "XML(*.xml)|*.xml";
            fileOpenDialog.InitialDirectory = ".";
            fileOpenDialog.ShowDialog();
            fileNameTextBox.Text = fileOpenDialog.FileName;
        }

        /// <summary>
        /// User has chosen to open the 
        /// Not allowed if running the TSP algorithm.
        /// </summary>
        /// <param name="sender">Object that generated this event.</param>
        /// <param name="e">Event arguments.</param>
        private void openCityListButton_Click(object sender, EventArgs e)
        {
            string fileName = "";

            try
            {
                if (tsp != null)
                {
                    StatusLabel.Text = "Cannot alter city list while running";
                    StatusLabel.ForeColor = Color.Red;
                    return;
                }

                fileName = this.fileNameTextBox.Text;
                
                cityList.OpenCityList(fileName);
                DrawCityList(cityList);
            }
            catch (FileNotFoundException)
            {
                MessageBox.Show("File not found: " + fileName, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error, MessageBoxDefaultButton.Button1, MessageBoxOptions.DefaultDesktopOnly);
            }
            catch (InvalidCastException)
            {
                MessageBox.Show("Cities XML file is not valid", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error, MessageBoxDefaultButton.Button1, MessageBoxOptions.DefaultDesktopOnly);
            }
        }

        /// <summary>
        /// User has selected to clear the city list.
        /// Not allowed if running the TSP algorithm.
        /// </summary>
        /// <param name="sender">Object that generated this event.</param>
        /// <param name="e">Event arguments.</param>
        private void clearCityListButton_Click(object sender, EventArgs e)
        {
            if (tsp != null)
            {
                StatusLabel.Text = "Cannot alter city list while running";
                StatusLabel.ForeColor = Color.Red;
                return;
            }

            cityList.Clear();
            this.DrawCityList(cityList);
        }

        /// <summary>
        /// User clicked a point on the city map.
        /// As long as we aren't running the TSP algorithm,
        /// place a new city on the map and add it to the city list.
        /// </summary>
        /// <param name="sender">Object that generated this event.</param>
        /// <param name="e">Event arguments.</param>
        private void tourDiagram_MouseDown(object sender, MouseEventArgs e)
        {
            if (tsp != null)
            {
                StatusLabel.Text = "Cannot alter city list while running";
                StatusLabel.ForeColor = Color.Red;
                return;
            }

            cityList.Add(new City(e.X, e.Y));
            DrawCityList(cityList);
        }

        /// <summary>
        /// Display the number of cities on the form.
        /// </summary>
        private void updateCityCount()
        {
            this.NumberCitiesValue.Text = cityList.Count.ToString();
        }
    }
}