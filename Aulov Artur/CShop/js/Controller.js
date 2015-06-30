var myApp = angular.module('myApp', []);

var height_u = $(".mainContent").height();

var gds = [];
gds[0] = {
    img: "image/base/record_159099587.jpg",
    name: "Sony XPeria Z3",
    price: '13 999',
    description: "Very Very Very nice smartphone.",
    category: 'Mobile'
}
gds[1] = {
    img: "image/base/record_637051567.jpg",
    name: "LG G4",
    price: '700',
    description: "Piu piu, now with a laser autofocus.",
    category: 'Mobile'
}
gds[2] = {
    img: "image/base/record_58250629.jpg",
    name: "HTC M8",
    price: '650',
    description: "50/50",
    category: 'Mobile'
}
gds[3] = {
    img: "image/base/record_164482757.jpg",
    name: "iPhone 6 Gold",
    price: '700',
    description: "Useless device.",
    category: 'Mobile'
}
gds[4] = {
    img: "image/base/record_451683577.jpg",
    name: "Samsung Galaxy S6",
    price: '1000',
    description: "Edge, just, edge, smartphone...",
    category: 'Mobile'
}
gds[5] = {
    img: "image/base/record_549743367.jpg",
    name: "Asus ROG",
    price: '2300',
    description: "Biggest machine.",
    category: 'Computers'
}
gds[6] = {
    img: "image/base/record_148900277.jpg",
    name: "Everest Game",
    price: '1100',
    description: "Oh...my dream.",
    category: 'Computers'
}
gds[7] = {
    img: "image/base/asus_ux301la_c4061h_blue_12279415.jpg",
    name: "Asus ZenBook",
    price: '1300',
    description: "Light and slime.",
    category: 'Computers'
}
gds[8] = {
    img: "image/base/record_182458692.jpg",
    name: "Dell Inspiron",
    price: '1000',
    description: "Gamers love this.",
    category: 'Computers'
}
gds[9] = {
    img: "image/base/record_231559982.jpg",
    name: "MSI Dominator",
    price: '1650',
    description: "One machine one love.",
    category: 'Computers'
}
gds[10] = {
    img: "image/base/record_585533512.jpg",
    name: "Author Dexter",
    price: '400',
    description: "Transport in future.",
    category: 'Relax'
}
gds[11] = {
    img: "image/base/record_117945700.jpg",
    name: "Sol Tourist",
    price: '150',
    description: "Sleepy sleepy sheep sheep...ZzZzZ...",
    category: 'Relax'
}
gds[12] = {
    img: "image/base/record_194592167.jpg",
    name: "Monopoly",
    price: '50',
    description: "All is mine!",
    category: 'Relax'
}
gds[13] = {
    img: "image/base/record_347423407.jpg",
    name: "Suunto Ambit3",
    price: '600',
    description: "What time is it?",
    category: 'Relax'
}
gds[14] = {
    img: "image/base/1854505.jpg",
    name: "Celestron AstroMaster",
    price: '250',
    description: "I see in the future",
    category: 'Relax'
}
gds[15] = {
    img: "image/base/record_657171485.jpg",
    name: "Pen",
    price: '2',
    description: "Write your life.",
    category: 'Stationery'
}
gds[16] = {
    img: "image/base/record_589950872.jpg",
    name: "Rubber bands",
    price: '3',
    description: "Many many many rubbers.",
    category: 'Stationery'
}
gds[17] = {
    img: "image/base/record_755294333.jpg",
    name: "Edding Highlighter",
    price: '2',
    description: "I love draw.",
    category: 'Stationery'
}
gds[18] = {
    img: "image/base/record_824604470.jpg",
    name: "Compasses",
    price: '7',
    description: "My first perfect circle.",
    category: 'Stationery'
}
gds[19] = {
    img: "image/base/record_719930104.jpg",
    name: "Data Copy A4",
    price: '3',
    description: "Papers, please.",
    category: 'Stationery'
}
gds[20] = {
    img: "image/base/fitlogic_freewill_r115_6587715.jpg",
    name: "FitLogic Freewill",
    price: '900',
    description: "Run forest! Run!",
    category: 'Health'
}
gds[21] = {
    img: "image/base/record_488409737.jpg",
    name: "Newt 17.5kg",
    price: '50',
    description: "Pick up this sh*t.",
    category: 'Health'
}
gds[22] = {
    img: "image/base/record_604912722.jpg",
    name: "CardioDock",
    price: '120',
    description: "Tuk Tuk Tuk...",
    category: 'Health'
}
gds[23] = {
    img: "image/base/art_choice_mia_light_beige_9005911.jpg",
    name: "Art of Choice JOY",
    price: '150',
    description: "Touch my back.",
    category: 'Health'
}
gds[24] = {
    img: "image/base/record_90540669.jpg",
    name: "Reebook ball",
    price: '40',
    description: "SKATE.",
    category: 'Health'
}
gds[25] = {
    img: "image/base/record_26817505.jpg",
    name: "Ukulele Diamond Head",
    price: '50',
    description: "Like in Miami.",
    category: 'Music'
}
gds[26] = {
    img: "image/base/hohner_big_river_c_9323473.jpg",
    name: "Hohner Big River",
    price: '30',
    description: "I love blues.",
    category: 'Music'
}
gds[27] = {
    img: "image/base/record_53974065.jpg",
    name: "Maxtone MXC3005",
    price: '340',
    description: "Make a surprise neighbors ",
    category: 'Music'
}
gds[28] = {
    img: "image/base/record_9729390.jpg",
    name: "Midi controller",
    price: '260',
    description: "Be a Skrillex",
    category: 'Music'
}
gds[29] = {
    img: "image/base/record_19122154.jpg",
    name: "Soundking SK",
    price: '480',
    description: "King of sound",
    category: 'Music'
}


myApp.controller("Controller", function ($scope) {
    this.product = gds;
    this.resetProd = function () {
        this.newProd = {
            img: "",
            name: "",
            price: '',
            description: "",
            category: ''
        }
    }
    this.resetProd();
    this.addProd = function () {
        this.newProd.prise = this.newProd.price + " $"
        this.product.push(this.newProd);
        this.resetProd();
        if (this.product.length % 3 == 0) {
            height_u += 540;
            $(".mainContent").css("height", height_u);
            $(".content").css("height", $(".mainContent").height() - $(".footer").height());
        }
    }
});