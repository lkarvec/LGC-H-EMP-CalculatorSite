import logo from './logo.svg';
import React, { Component } from "react";
import './App.css';
import Inputs from './components/inputs'
import Graph from './components/graph'
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
        val is default value given by Henry, 
        variable is the variable name in the equation to be displayed by the GUI
        */
        {id: 1, val: 0, variable: 'x', variableName: 'x'},
        {id: 2, val: 0, variable: 'y', variableName: 'y'},
        {id: 3, val: 0, variable: 'z', variableName: 'z'},
        {id: 4, val: 70, variable: 'Height of Burst', variableName: 'HOB'},
        {id: 5, val: 0, variable: 'Gamma', variableName: 'G'},
        {id: 6, val: 0, variable: 'Magnitude of Magnetic Field', variableName: 'MAG'},
        {id: 7, val: 20, variable: 'Dip Angle of Magnetic Field', variableName: 'DIP'},
        {id: 8, val: 50, variable: 'NDELR', variableName: 'NDELR'},
        {id: 9, val: 10, variable: 'ITERATIONS', variableName: 'ITER'},
        {id: 10, val: 0, variable: 'A', variableName: 'A'},
        {id: 11, val: 0, variable: 'B', variableName: 'B'},
        {id: 12, val: 0, variable: 'RNP', variableName: 'RNP'},
        {id: 13, val: 0, variable: 'TOP', variableName: 'TOP'}
    ],
    data: [

    ],
    output: {output:""}
 }

 handleInputs = () => {
  console.log('Submit clicked');


  //this.setState({ output })
  //graph.setState({});
};



 render() {
  return (
    <React.Fragment>
    <div className="App">
      <header className="App-header">
        <div>
          <img src={logo} className="App-logo" alt="logo" />
          <text>
            H-EMP Calculator
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
      </div>

      <div className="Footer" style={{display: 'flex',  justifyContent:'center', alignItems:'center'}}>
        <p style={{justifyContent:'center', alignItems:'center'}}>
        <div style={{display: 'flex',  justifyContent:'center', alignItems:'center'}}><a
          href="https://reactjs.org"
          target="_blank"
          rel="noopener noreferrer"
          className="Doc-link"
        >
          GitHub 
        </a></div>
         Made by Alexander Mains and Dr. Mark Robinson
        </p>
      </div>
      
    </div>
    </React.Fragment>
  );
 }
}

export default App;
