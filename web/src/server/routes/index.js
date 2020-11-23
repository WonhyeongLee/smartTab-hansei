const express = require('express');
const router = express.Router();

router.get('/', function(req, res){
    res.send({greeting: 'React + Nodejs 연동 테스트'});
});

module.exports = router;

