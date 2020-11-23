//메인서버
const express = require('express');
const app = express();
const api = require('./routes/index');
const bodyParser = require('body-parser');
const db_config = require('./config/dbconfig');
const conn = db_config.init();
const cors = require('cors');
const port = 3002;

db_config.connect(conn);

app.use(cors());
app.use(bodyParser.json());
app.use('/api',api);

app.get("/db", (req,res)=>{
    const sql = "SELECT * FROM refrigerater";
    conn.query(sql,function(err,rows,fields){
        if(err){
            console.log("DB조회실패" + err);
        }else{
            console.log(rows);
            res.send(rows);
        }
    })

})

app.listen(port, ()=>console.log(`Listening on port ${port}`));

// app.get("/*", function (req,res){
//     res.sendFile(__dirname + "../../dist/index.html");
// });
