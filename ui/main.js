GREAT_BORDER_COLOR = "#724938";
LESS_BORDER_COLOR = "#B35C37";
BACKGROUND_COLOR = "#FFFFFF";
SELECTED_COLOR = "#DB8E71"; //"#AF5F3C";
RELATED_COLOR = "#EEDED7";
UNFIXED_COLOR = LESS_BORDER_COLOR; //"#DB8E71";
SAME_COLOR = "#F9BF45";
MARKED_COLOR = "#F4A7B9";
PAUSE_COLOR = "#AAAAAA";
BLACK_COLOR = "#000000";

BOARD_WIDTH = 10;

// initializer
function initGameTable() {
    for (var i = 0; i < BOARD_WIDTH; ++i) {
        var tr = $("<tr></tr>");
        for (var j = 0; j < BOARD_WIDTH; ++j) {
            var td = $("<td class=\"cell cell_" + ((i + j) % 2 == 0 ? "white" : "dark") + "\" id=\"cell" + i + j + "\" onclick=\"onCellClick(" + i + ", " + j + ")\"></td>");
            tr.append(td);
        }

        $("table.table_main").append(tr);
    }
}

function onRoleChosen(v) { window.channel.onRoleChosen(v); }

function onCellClick(i, j) {
    window.channel.onCellClick(i, j);
}
