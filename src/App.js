import logo from './logo.svg';
import React, { Component } from "react";
import './App.css';
import Inputs from './components/inputs'
import Graph from './components/graph'
import utilities from '../misc/utilities';
//import Button from './components/button' not used
/*
TODO: Make ParseIter function for EField Values at Target
Make ParseIter function for Times Used (IN SHAKES)
Use Axios for the frontend to call the API
*/
class App extends Component {
  state = { 
    inputs: [ 
        /*
        val is default value given by Henry, Used in the Seiler Thesis, 
        variable is the variable name in the equation to be displayed by the GUI
        This is an array of 13 OBJECTS
        ID is how to access them and is purely referential
        */
        {id: 0, val: 0, variable: 'x', variableName: 'x'},
        {id: 1, val: 0, variable: 'y', variableName: 'y'},
        {id: 2, val: 0, variable: 'z', variableName: 'z'},
        {id: 3, val: 100, variable: 'Height of Burst', variableName: 'HOB'},
        {id: 4, val: 0.001, variable: 'Gamma', variableName: 'G'},
        {id: 5, val: 0.00002, variable: 'Magnitude of Magnetic Field', variableName: 'MAG'},
        {id: 6, val: 20, variable: 'Dip Angle of Magnetic Field', variableName: 'DIP'},
        {id: 7, val: 50, variable: 'NDELR', variableName: 'NDELR'},
        {id: 8, val: 10, v4ariable: 'ITERATIONS', variableName: 'ITER'},
        {id: 9, val: 2.2, variable: 'A for inverse shakes', variableName: 'A'},
        {id: 10, val: 0.25, variable: 'B for inverse shakes', variableName: 'B'},
        {id: 11, val: 5.62603, variable: 'N for shakes', variableName: 'RNP'},
        {id: 12, val: 2.24, variable: 'T0 for shakes', variableName: 'TOP'}
    ],
    data: {},
    output: {},
    error: []
 }
/*curl -X 'POST' \
  'https://slim1.fulgentcorp.com:14500/emp/calc' \
  -H 'accept: application/json' \
  -H 'Content-Type: application/json' \
  -d '{
  "x": 0,
  "y": 0,
  "z": 0,
  "hob": 0,
  "gamyld": 0,
  "bfield": 0,
  "bangle": 0,
  "ndelr": 0,
  "oux": 0,
  "iter": 0,
  "ap": 0,
  "bp": 0,
  "rnp": 0,
  "top": 0
}*/
//Send a request to DocRobs Fulgent server with the params described above
// === fetch generated from https://kigiri.github.io/fetch/ and changed to fit our project.  Very useful tool!
 handleInputs = () => {
//add input checking
  try{
    utilities.inputCheck(this.state.inputs);
  }catch(error){
    console.error(error);
    this.setState({output:error})
    break;
  }
  
  let bodyInputs = utilities.formatBody(this.state.inputs);

  console.log('Clicked the button');
  
  await fetch('https://slim1.fulgentcorp.com:14500/emp/calc', {
  body: bodyInputs,
  headers: {
    'Accept': "application/json",
    'Content-Type': "application/json"
  },
  method: 'POST'
})
  .then(res => res.json())
  .then(
    (result) => {
      this.setState({
        data: JSON.parse(result.message)
      });
      console.log('Set the Data : cutting the Json up');
      this.regexForOutput;
    },
    //error catch here so we can bug catch from the fetch and get more descriptive error checking.
    (error) => {
      this.setState({
       error
      });
    }
    )

};

regexForOutput = () => {
  this.setState({output: utilities.skim(this.state.data)})
  console.log('Set the Output : going to regex');

};

/* Structure of page
Full page
  Header
    Logo + Title
  Body
    Input div
      All of the Input Fields
      Output
    Submit button
    Graphs
  Footer
    Credit Text and Links
*/

 render() {
  return (
    <React.Fragment>
    <div className="App">
      <header className="App-header">
        <div>
          <img src={logo} className="App-logo" alt="logo" />
          <text>
            High Altitude EMP - Calculator
          </text>
        </div>
      </header>

      <div className="Body">
        

        <div className="Input-Row">
          <Inputs
            inputs={this.state.inputs}/>
          <textarea className="Output"
          value={this.state.output}
          >
            
          </textarea>
        </div>

        <div className="Button">
          <button  
            className="btn btn-primary btn-sm m-1"
            onClick={this.handleInputs}>
              Submit
          </button>
        </div>

        <div className="GraphShakes">
          <Graph></Graph>
        </div>
      </div>

      <div className="Footer" style={{display: 'flex',  justifyContent:'center', alignItems:'center'}}>
        <p style={{justifyContent:'center', alignItems:'center'}}>
        <div style={{display: 'flex',  justifyContent:'center', alignItems:'center'}}><a
          href="https://github.com/lkarvec/LGC-H-EMP-CalculatorSite"
          target="_blank"
          rel="noopener noreferrer"
          className="Doc-link"
        >
          GitHub 
        </a></div>
         Made by Alexander Mains and Dr. Mark Robinson
         Sponsored by the Louisiana Grid Coalition
        </p>
      </div>
      
    </div>
    </React.Fragment>
  );
 }
}

export default App;
