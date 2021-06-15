# WORK IN PROGRESS

###TO DO
Figure out hosting solutions and if they will require dockerization - note; EMPS offered help;
Contact the CanvasJS tech team to figure out the height sizing issue of the graph
Clean up C++ from Tin

#High Altitude Electro-Magnetic Pulse Calculator
In March 1975, Louis W. Seiler, Jr published a paper for the Air Force Institute of Technology to evaluate the effects of Electro-Magnetic Pulse.  Provided within the original document was the calculation methods in Fortran.  This program is a product of their research.

##Variables for the Equation
####X
Magnetic west (Northern Hemisphere)
####Y
Magnetic South (Northern Hemisphere)
####Z
Altitude (Northern Hemisphere)
####HOB
Height of Burst in Kilometers (has to be greater than 50KM)
####GAMYLD
Gamma Yield of Burst in Kilotons
####BFIELD
Magnitude of Earth's Magnetic Field in the absorption region below the burst in Webers/Sq Meter
####BANGLE
Dip angle of the Magnetic Field in degrees
####NDELR
Integer number of steps between RMin and RMax (Has to be between 50 and 500)
####ITER
Time of Iterations in Shakes (from 10 to 100)
###Pomranning Constants
####AP
####BP
####RNP
####TOP

# Getting Started with Create React App

This project was bootstrapped with [Create React App](https://github.com/facebook/create-react-app).

## Available Scripts

In the project directory, you can run:

### `npm start`

Runs the app in the development mode.\
Open [http://localhost:3000](http://localhost:3000) to view it in the browser.

The page will reload if you make edits.\
You will also see any lint errors in the console.

### `npm test`

Launches the test runner in the interactive watch mode.\
See the section about [running tests](https://facebook.github.io/create-react-app/docs/running-tests) for more information.

### `npm run build`

Builds the app for production to the `build` folder.\
It correctly bundles React in production mode and optimizes the build for the best performance.

The build is minified and the filenames include the hashes.\
Your app is ready to be deployed!

See the section about [deployment](https://facebook.github.io/create-react-app/docs/deployment) for more information.

### `npm run eject`

**Note: this is a one-way operation. Once you `eject`, you can’t go back!**

If you aren’t satisfied with the build tool and configuration choices, you can `eject` at any time. This command will remove the single build dependency from your project.

Instead, it will copy all the configuration files and the transitive dependencies (webpack, Babel, ESLint, etc) right into your project so you have full control over them. All of the commands except `eject` will still work, but they will point to the copied scripts so you can tweak them. At this point you’re on your own.

You don’t have to ever use `eject`. The curated feature set is suitable for small and middle deployments, and you shouldn’t feel obligated to use this feature. However we understand that this tool wouldn’t be useful if you couldn’t customize it when you are ready for it.
