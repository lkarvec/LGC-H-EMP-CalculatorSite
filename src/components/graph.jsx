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
var CanvasJSReact = require('../canvasjs.react');
var CanvasJSChart = CanvasJSReact.CanvasJSChart;
 
class Graph extends Component {
	constructor() {
		super();
		this.generateDataPoints = this.generateDataPoints.bind(this);
	}
	
	generateDataPoints(noOfDps) {
		var xVal = 1, yVal = 100;
		var dps = [];
		for(var i = 0; i < noOfDps; i++) {
			yVal = yVal +  Math.round(5 + Math.random() *(-5-5));
			dps.push({x: xVal,y: yVal});	
			xVal++;
		}
		return dps;
	}
	state = { 
			theme: "dark2", // "light1", "dark1", "dark2"
			animationEnabled: true,
			zoomEnabled: true,
			title: {
				text: "Try Zooming and Panning"
			},
			data: [{
				type: "area",
				dataPoints: this.generateDataPoints(500)
			}]
		}
	
	
	render() {
		
		
		return (
		<div>
			<CanvasJSChart options = {this.state} 
				/* onRef={ref => this.chart = ref} */
			/>
			{/*You can get reference to the chart instance as shown above using onRef. This allows you to access all chart properties and methods*/}
		</div>
		);
	}
}
 
export default Graph;                        