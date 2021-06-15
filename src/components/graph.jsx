/*var React = require('react');
var Component = React.Component;
var CanvasJSReact = require('./canvasjs.react');
var CanvasJSChart = CanvasJSReact.CanvasJSChart;
 
export default class Graph extends Component {
	constructor() {
		super();
	}
	
	render() {
		const options = {
			theme: "dark1", // "light1", "dark1", "dark2"
			animationEnabled: true,
			zoomEnabled: true,
            exportEnabled: true,
			title: {
				text: ""
			},
			data: [{
				type: "area",
				dataPoints: this.props.data
			}]
		}
		
		return (
		<div>
			<CanvasJSChart options = {options} 
				/* onRef={ref => this.chart = ref} 
			/>
			//You can get reference to the chart instance as shown above using onRef. This allows you to access all chart properties and methods}
		</div>
		);
	}
}

//dataPoints: this.props.data
*/
/* App.js */
import React, { Component } from 'react'
import CanvasJSReact from '../canvasjs.react';
var CanvasJS = CanvasJSReact.CanvasJS;
var CanvasJSChart = CanvasJSReact.CanvasJSChart;
 
class Graph extends Component {
	
	state = { 
			theme: "dark2", // "light1", "dark1", "dark2"
			animationEnabled: true,
			zoomEnabled: true,
			title: {
				text: "Times Used (IN SHAKES)"
			},
			data: [{
				type: "area",
				dataPoints:[{x:1,y:1},{x:2,y:3},{x:3,y:6},{x:4,y:1},{x:5,y:2}]
			}]
		}
	
	
	render() {
		
		
		return (
		<React.Fragment>
			<CanvasJSChart options = {this.state} 
				/* onRef={ref => this.chart = ref} */
			/>
			</React.Fragment>
		);
	}
}
 
export default Graph;                        