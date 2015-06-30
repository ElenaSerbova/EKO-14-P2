// JavaScript source code
var last = null;
var firstnod;
var curntnod;
var forconnect1 = null;
var forconnect2 = null;

function addchild(nod, childnod) {
    if (nod.ty == 'block' && nod.child.length == 1) {

    }
    else {
        if (nod.ty == 'if') {
            if (nod.child.length == 1) {
                childnod.x += childnod.size / 2 + 40;
            }
            else {
                childnod.x -= childnod.size / 2 + 40;
            }
        }
        if (nod.child.length < 2) {
            nod.child[nod.child.length] = childnod;
            childnod.parent[childnod.parent.length] = nod;
        }
    }
}

function nod(x, y, size, parent, text, ty) {
    this.size = text.length * 10;
    this.x = x;
    this.y = y;
    this.parent = [];
    this.parent[0] = parent;
    this.text = text;
    this.ty = ty;
    this.child = [];
    this.drow = function (ctx) {
        if (curntnod == this) {
            ctx.fillRect(this.x - 30, this.y - 15, 3, 3);
        }
        switch (ty) {
            case 'block':
                ctx.strokeRect(this.x - this.size / 2, this.y - 15, this.size, 30);
                ctx.font = "20px serif";
                ctx.fillText(this.text, this.x - this.size / 2 + 1, this.y + 2)
                break;
            case 'begin':
                ctx.font = "20px serif";
                ctx.beginPath();
                ctx.ellipse(this.x, this.y, this.size / 2 + 5, 15, 0, 0, 2 * Math.PI);
                ctx.closePath()
                ctx.stroke();
                ctx.fillText(this.text, this.x - this.size / 2 + 1, this.y + 2)
                break;
            case 'end':
                ctx.font = "20px serif";
                ctx.beginPath();
                ctx.ellipse(this.x, this.y, this.size / 2 + 5, 15, 0, 0, 2 * Math.PI);
                ctx.closePath()
                ctx.stroke();
                ctx.fillText(this.text, this.x - this.size / 2 + 1, this.y + 2)
                break;
            case 'if':
                ctx.font = "8px serif";

                ctx.beginPath();
                ctx.font = "20px serif";
                ctx.fillText("1", this.x - this.size, this.y + 5)
                ctx.fillText("0", this.x + this.size, this.y + 5)
                ctx.moveTo(this.x, this.y - 15);
                ctx.lineTo(this.x - (this.size / 1.5), y);
                ctx.lineTo(this.x, y + 15);
                ctx.lineTo(this.x + (this.size / 1.5), y);
                ctx.lineTo(this.x, this.y - 15);
                ctx.closePath()
                ctx.stroke();
                ctx.fillText(this.text, this.x - this.size / 2 + 1, this.y + 5)
                break;
        }
    }
}

function update() {
    if (canvas.getContext) {
        var ctx = canvas.getContext('2d');
        ctx.clearRect(0, 0, canvas.width, canvas.height);
        nextnod(firstnod);
    }
}

function nextnod(nod) {
    nod.drow(ctx);
    for (var i = 0; i < nod.child.length; i++) {
        ctx.beginPath();
        ctx.moveTo(nod.x, nod.y + 15);
        ctx.lineTo(nod.child[i].x, nod.child[i].y - 15);
        ctx.closePath();
        ctx.stroke();
        nextnod(nod.child[i])
    }
}

$('#butt').click(function () {
    addchild(curntnod, new nod(curntnod.x, 40 + curntnod.y, 50, curntnod, $('#text')[0].value, 'block'));
    update();
});

$('#ifbutt').click(function () {
    addchild(curntnod, new nod(curntnod.x, 40 + curntnod.y, 50, curntnod, $('#text')[0].value, 'if'));
    update();
});

$('#up').click(function () {
    if (curntnod.parent[0])
        curntnod = curntnod.parent[0];
    update();
});

$('#right').click(function () {
    if (curntnod.child[1] !== undefined)
        curntnod = curntnod.child[1];
    update();
});

$('#left').click(function () {
    if (curntnod.child[0] !== undefined)
        curntnod = curntnod.child[0];
    update();
});

$('#end').click(function () {
    addchild(curntnod, new nod(curntnod.x, 40 + curntnod.y, 50, curntnod, 'end', 'end'));
    update();
});

$('#connect').click(function () {
    if (forconnect1 == null) {
        forconnect1 = curntnod;
    }
    else {
        forconnect2 = curntnod;
        addchild(forconnect1, forconnect2);
        update();
    }
});

var canvas = $('#canv')[0];
if (canvas.getContext) {
    var ctx = canvas.getContext('2d');
    ctx.strokeRect(10, 10, 50, 50);
}

firstnod = new nod(canvas.width / 2, 20, 20, null, 'Begin', 'begin', null);
curntnod = firstnod;
update();