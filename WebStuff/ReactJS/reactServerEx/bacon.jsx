
//Create a component.
/*  //No jsx
      class Bacon extends React.Component {
        render() {
            return React.createElement('h2',null,'This is a simple component.')
        }
      }
      ReactDOM.render(
        React.createElement(Bacon, null),
        document.getElementById('root')
      );
*/

//Create a component.
      class Bacon extends React.Component {
        render() {
//Returns html.    
//using jsx      
          return (<h2>peen.</h2>);
        }
      }


//Using jsx
      ReactDOM.render(
        <Bacon />,
        document.getElementById('root')
      );


