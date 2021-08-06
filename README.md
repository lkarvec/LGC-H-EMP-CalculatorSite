# WORK IN PROGRESS

### TO DO
Figure out hosting solutions - note; EMPS offered help;

Contact the CanvasJS tech team to figure out the height sizing issue of the graph

Clean up C++ from Tin

Connect the API to the front end

Create CI/CD (not necessary for our current hosting solution but good practice)

### Known Issues
CanvasJS graph doesn't resize height properly

Margins look funky, Fix at the end

Output box has a state change issue, might be solved later once everything is connected, Priority 1 of issues

# High Altitude Electro-Magnetic Pulse Calculator
In March 1975, Louis W. Seiler, Jr published a paper for the Air Force Institute of Technology to evaluate the effects and calculation methods of Electro-Magnetic Pulse.  Provided within the original document was the calculation methods in Fortran.  This program is a product of their research, transitional code from Tin Muang, and Front-end and maintenance efforts by Dr. Mark Robinson and Leon Karvecz.  [Henry Newton](https://www.linkedin.com/in/henry-newton-3161bab/) is the sponsor of this project and provided all of the materials for us.

This coding expresses modifications to the original Fortran coding in a free Thesis by Terry Chapman of the USAF open source federal catalog number - [ADO 777841](https://apps.dtic.mil/sti/pdfs/AD0777841.pdf), or the rewrite at  ‘GitHub.com’ for  6448 volts/meter at [the LA Grid Coalition's publicly available EMP Library on GitHub](https://github.com/LAGridCoalition), 

The original coding has been re-written into C++ but operated only from the console. This coding provides a front end and back end that updates the framework and makes it accessible to the public.

The electromagnetic threat for this software focusses on large instantaneous destructive electromagnetic pulse (EMP) with a wavelength of 10 to the minus 7 power. A EMP event can destroy equipment (hardware and software) that enable the functioning of the entire society in the United States. A large and electromagnetic event can shut down power and damage critical systems across large regions or even the entire United States. The E1 portion is only explored in the Thesis and the E1 waveform is shown to be 50,000 v/M as a DC pulse which destroys items such as transistors and other microelectronics as well as large and small Utility power transformers per the AF Thesis written by [Louis Seiler in 1975](http://large.stanford.edu/courses/2019/ph241/rogers1/docs/ad-a009-208.pdf), 

A shutdown could result in portions or the entirety of the nation operating without power for weeks or months. A successful attack means no electricity, no communications, no financial transactions, no water, no food, no transportation, and all other infrastructure that requires power will cease to function. Some of these infrastructures will degrade over hours or several days, others will cease immediately. See https://www.amazon.com/gp/product/B08NF79YGX,  for a NDRC book on the subject. 

Also, the free “Electromagnetic Defense Task Force Report” by the USAF in March 2019, and it paints a sad picture of EMP. The Air Force report estimates that as much as 90 percent of the East Coast population will die within a year due to the lack of basic human needs, and the chaos resulting from an EMP. See https://www.airuniversity.af.edu/Portals/10/AUPress/Papers/LP_0004_ELECTROMAGNETIC_DEFENSE_TASK_FORCE_2_2019.PDF, 


This product is open-source and free to use.  Feel free to contact Leon Karvecz at lkarvec@gmail.com for questions about the project.

Command to hit the API is located in CURL.MD

## Variables for the Equation
#### X
Magnetic west (Northern Hemisphere)
#### Y
Magnetic South (Northern Hemisphere)
#### Z
Altitude (Northern Hemisphere)
#### HOB
Height of Burst in Kilometers (has to be greater than 50KM)
#### GAMYLD
Gamma Yield of Burst in Kilotons
#### BFIELD
Magnitude of Earth's Magnetic Field in the absorption region below the burst in Webers/Sq Meter
#### BANGLE
Dip angle of the Magnetic Field in degrees
#### NDELR
Integer number of steps between RMin and RMax (Has to be between 50 and 500)
#### ITER
Time of Iterations in Shakes (from 10 to 100)
### Pomranning Constants
#### AP
#### BP
#### RNP
#### TOP

# Create React App additions

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
