import React, { Component } from 'react'
import Input from "./input"

export default class Inputs extends Component{
    
    render() { 
        return ( 
            <div className="Input-Space"> 
                {this.props.inputs.map(input => (
                    <Input key={input.id}
                    input={input}
                />))}
            </div> 
        );
    }
}
 
