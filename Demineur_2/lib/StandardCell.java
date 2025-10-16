package lib;

public class StandardCell extends AbstractCell {
    public StandardCell() {
        super();
        this.bomb = false;
    }

    public String toString() {
        return isRevealed() 
            ? (adjacentBombs > 0 ? String.valueOf(adjacentBombs) : " ") 
            : ".";
    }
}
