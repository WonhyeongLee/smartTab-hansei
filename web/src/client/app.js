import React, {Component} from 'react';

export default class App extends Component{
constructor(props){
    super(props);
    this.state = { name: "" };
}
// componentDidMount(){
//     fetch('http://localhost:3002/api1')
//     .then(res=>res.json())
//     .then(data=>this.setState({username:data.username}));
// }
    render(){
        //const {username} = this.state;
        return (
            <div className="container">

              TEST 입니다.
            </div>
        );
    }
}

