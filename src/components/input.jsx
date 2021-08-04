import React, { Component } from 'react'

class Input extends Component{
    /*state = { 
        val: this.props.val,
        variable: this.props.variable
     }*/
    render() { 
        
        return ( 
            <div> 
                <label>{this.props.input.variable}</label><br/>
                <input
                    className="Single-Input"
                    type="number"
                    placeholder={this.props.input.variableName}
                    value={this.props.input.value}
                    //onChange={event => console.log("value changed!")}
                    
                /><br/>
                
            </div> 
        );
    }
}

export default Input;