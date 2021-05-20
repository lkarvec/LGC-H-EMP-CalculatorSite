let express = require('express');
let router = express.Router();

const utilities = require("../misc/utilities");
const logger = utilities.getLogger();

var exec = require('child_process').exec;

// I like to log who is calling the web services
router.use(function (req, res, next) {
    const ip = utilities.getRequestIPAddress(req);
    logger.info("Properties request route " + req.originalUrl + " from " + ip);
    next();
});

// this is the top-level GET route for the /properties router
router.post('/calc/',
  async function(request, response) {
        // validate input
        let body = request.body;
        console.log(body);
        
        // run calculator/a.out
        await exec("calculator/a.out", function(error, stdout, stderr) { 
            if(error) {
                logger.info("server error");
                let result = "server error";
                utilities.sendResponse(response, 500, result);
            } else {
                logger.info("calculator success");
                utilities.sendResponse(response, 200, stdout);
            }
        });
    }
);

module.exports = router;

