// LOGGING SETUP
const winston = require('winston');
require('winston-daily-rotate-file');

const transport = new (winston.transports.DailyRotateFile)({
  filename: 'logs/hemp-api-%DATE%.log',
  datePattern: 'YYYY-MM-DD',
  zippedArchive: true,
  maxFiles: '28d'
});

let logger = null;

module.exports = {

	inputCheck : (inputs) =>{
		let returnMesg = ""
		//Check x input *** check X Y Z Later, Talk to Henry
		//if (Math.sign(inputs[0].val) == 1){
			//}
		// Height of burst needs to be 60+ Kilometers
		if (!(60 <= inputs[3].val)){
			returnMesg += "\n Height of Burst (HOB) needs to be more than 60 Kilometers\n"
			}
		//Gamma Yield needs to be below 1 Kiloton
		if (!(inputs[4].val <= 1)){
			returnMesg += "\n Gamma Yield (G) needs to be below 1 Kiloton\n"
			}
			//Dip angle needs to be -90 - 90
		if (!(-90 <= inputs[6].val >= 90)){
			returnMesg += "\n Dip Angle (DIP - https://en.wikipedia.org/wiki/Magnetic_dip) needs to be between -90 and 90\n"
			}
		if (!(50 <= inputs[7].val <= 500) && !(Integer.parseInt(inputs[8].val)) ){
			returnMesg += "\n NDELR needs to be an int between 50 and 500\n"
		}
		// Make sure the iterations is an int between 10-100
		if (!(10 <= inputs[8].val <= 100) && !(Integer.parseInt(inputs[8].val)) ){
			returnMesg += "\n Iterations (ITER) needs to be an int between 10 and 100\n"
		}
		//if return isn't empty, throw it as an error for the error handler to catch
		if (returnMesg != ""){
			throw returnMesg
		}
		// Fall out of function

	},

	formatBody : (inputs) => {
		let JSONOBJ = JSON.stringify({"x": inputs[0].val,             
									"y": inputs[1].val,
									"z": inputs[2].val,
									"hob": inputs[3].val,
									"gamyld": inputs[4].val,
									"bfield": inputs[5].val,
									"bangle": inputs[6].val,
									"ndelr": inputs[7].val,
									"oux": 0,
									"iter": inputs[8].val,
									"ap": inputs[9].val,
									"bp": inputs[10].val,
									"rnp": inputs[11].val,
									"top": inputs[12].val});
		return JSONOBJ;
	},




	skim : (message) => {
		//(I = (\d)+ : (\d+\.*\d*))  Regex for the skimmer
		let y1 = [];
		let y2 = [];
		
	},

	sendResponse: (response, code, msgJson) => {
    	// if msg is not json then wrap it in json
    	const msgType = module.exports.whatIsIt(msgJson);
    	if(msgType != "Array" && msgType != "Object")
    		msgJson = {"message":msgJson};
        response.status(code);
        response.setHeader('Content-Type', 'application/json');
        response.setHeader("Access-Control-Allow-Methods", "*");
        response.setHeader("Access-Control-Allow-Origin", "*");
        response.setHeader("Access-Control-Allow-Headers", "Content-Type, api_key, Authorization");
        response.send(msgJson);
        response.end();
    },
	getRequestIPAddress: (request) => {
		return request.headers['x-forwarded-for'] || request.connection.remoteAddress;
	},

	getLogger: () => {
		if(logger == null) {
			logger = winston.createLogger({
				level: 'debug',
				format: winston.format.combine(
				  winston.format.timestamp({
					format: 'YYYY-MM-DD HH:mm:ss'
				  }),
				  winston.format.errors({ stack: true }),
				  winston.format.splat(),
				  winston.format.prettyPrint()
				),
				defaultMeta: { service: 'hemp-api' },
				transports: [
				  transport
				]
			  });
		}
		return logger;
	},

	pad: (n, width, z) => {
		z = z || '0';
		n = n + '';
		return n.length >= width ? n : new Array(width - n.length + 1).join(z) + n;
	},
	
    whatIsIt: (object) => {
    	// borrowed from https://stackoverflow.com/questions/11182924/how-to-check-if-javascript-object-is-json
		const stringConstructor = "test".constructor;
		const arrayConstructor = [].constructor;
		const objectConstructor = ({}).constructor;

    	if (object === null) {
        	return "null";
    	}
    	if (object === undefined) {
        	return "undefined";
    	}
    	if (object.constructor === stringConstructor) {
        	return "String";
    	}
    	if (object.constructor === arrayConstructor) {
        	return "Array";
    	}
    	if (object.constructor === objectConstructor) {
        	return "Object";
    	}
        return "don't know";
    }
};