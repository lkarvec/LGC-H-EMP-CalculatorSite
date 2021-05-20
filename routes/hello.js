let express = require('express');
let router = express.Router();

const utilities = require("../misc/utilities");
const logger = utilities.getLogger();

// I like to log who is calling the web services
router.use(function (req, res, next) {
    const ip = utilities.getRequestIPAddress(req);
    logger.info("Hello request route " + req.originalUrl + " from " + ip);
    next();
});

// this is the top-level GET route for the /hello router
router.get('/',
  async function(request, response) {
        logger.info("success");

        utilities.sendResponse(response, 200, "return hello response here");
    }
);

module.exports = router;

