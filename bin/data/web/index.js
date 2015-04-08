function init() {
  var $container = $('#container');
  var $pointer = $('#pointer');

  // WebSocket Setup
  var ws = new WebSocket('ws://localhost:9092/');

  ws.onopen = function(event) {
    console.log('on open');
  };

  ws.onmessage = function(event) {
    var pos = JSON.parse(event.data);
    $pointer.css({left: pos.x - $pointer.width()/2, top: pos.y - $pointer.height()/2});
  }

  $container.mousemove(function(event){
    // console.log(event);
    var pos = { x: event.clientX, y: event.clientY};
    $pointer.css({left: pos.x - $pointer.width()/2, top: pos.y - $pointer.height()/2});
    ws.send(JSON.stringify(pos));
  });
}

window.onload = init;