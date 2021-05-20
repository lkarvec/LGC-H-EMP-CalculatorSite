import React, { Component } from 'react';
// create the class for the component used
export default class TextComponent extends Component {
    state = { 
        x: 0,
        
     }

     // How to bind a component to THIS.
     constructor() {
         super();
//       this.handler = this.handler.bind(this);
     }

/*
How to make a method
// e refers to the event handler below
     handler = ( e ) => {  
        // how to set state to a different thing
//      this.setState({ x: this.state.x + 1 }); if we were to increment x
     }
*/

/*
How to make an event handler
     doHandler = () => {
         this.handler({ id: 1});
     }
*/

/*
How to pass event arguments in your rendered code
This makes a button that handles an increment and updates another number on the screen
    render() { 
        return ( <div>
                    <span className={this.getBadgeClasses()}>{this.formatCount()}</span>
                    <button
                        onClick={ () => this.handleIncrement(e) } // e is the event handler
                        className="btn btnsecondary btn-sm"
                        >
                    Increment
                    </button>
                </div> );
    }
*/
    render() { 
        return ( <div>
                    <p>X</p>
                </div> );
    }
}
 
