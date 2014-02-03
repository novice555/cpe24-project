window.setInterval(function() {check()}, 10000);

function check() {
    $.ajax({
        url: "/cake/diffs/updatestat",
        dataType: 'json',
        //data: {"tag": tag},
        success: update,
        error: function(kuy) {
            console.log('error');
        }
    });
}

function update(st) {
    
    for(i in st) {
        //var a = document.getElementById(i);
        //console.log(a.innerHTML);
        //console.log($("#"+i)[0]);
        var text = $("#"+i);
    
        //console.log(text.length);
        if(text.length >= 1) {
            if(st[i]==0) {
                text[0].innerHTML = '<a href="/cake/diffs/view/'+i+'" class="glyphicon glyphicon-edit" target="_blank">Result</a>';
            } else if(st[i]==1) {
                text[0].innerHTML = 'In Queue';
            } else if(st[i]==2) {
                text[0].innerHTML = 'Process';
            } else if(st[i]==3) {
                text[0].innerHTML = 'Error';
            }
        }
        
    }
    
}

