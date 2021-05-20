import React, { Component } from 'react'

export default class Button extends Component {
    state = {  }
    handleInputs = () => {
        console.log('Submit clicked');
        //graph.setState({});
    };
    
    render() { 
        return ( <div>
            <button
                title="Submit"
                onClick={this.handleInputs}
                icon={{ name: 'check-circle', color: '#fff' }}
                iconContainerStyle={{marginRight: 50 }}
                buttonStyle={{ justifyContent: 'flex-start', width: 200 }}
            />
            </div>);
    }
}
