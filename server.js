require('dotenv').config();  
const utilities = require("./misc/utilities");
const logger = utilities.getLogger();

const https = require('https');
const fs = require('fs');

// https
const httpsOptions = {
    key: fs.readFileSync('keys/privkey.pem'),
    cert: fs.readFileSync('keys/fullchain.pem')
  };
  
// express makes web services for node easy
const express = require('express');

// init the express
const cors = require('cors');
const app = express();
app.use(express.json());
app.use(cors());

// hook up the routers
// property router handles all the routes that work with properties
const empRouter = require('./routes/emp');
app.use('/emp', empRouter);
// swagger router handles any swagger calls
const swaggerRouter = require('./routes/swagger');
app.use('/swagger', swaggerRouter);
// hello is misc functionality so throw it in its own router
const helloRouter = require('./routes/hello');
app.use('/hello', helloRouter);

https.createServer(httpsOptions, app).listen(process.env.HTTPS_LISTEN_PORT, function () {
    console.log('API server is listening on port ' + process.env.HTTPS_LISTEN_PORT + '...');
    logger.info('API server is listening on port ' + process.env.HTTPS_LISTEN_PORT + '...');
});
