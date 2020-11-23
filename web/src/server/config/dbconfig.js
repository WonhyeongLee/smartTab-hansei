const mysql = require('mysql');

const db_info= { 
        host:'localhost', 
        port:'3306', 
        user:'kkwon57', 
        password:'!q2w3e4r', 
        database:'foods'};

module.exports = {
        init: function () {
                return mysql.createConnection(db_info);
        },
        connect: function(conn) {
               conn.connect(function(err) {
                 if(err) console.error('mysql 접속 에러 : ' + err);
                 else console.log('mysql 접속 성공');
                 });
              }
        }
 