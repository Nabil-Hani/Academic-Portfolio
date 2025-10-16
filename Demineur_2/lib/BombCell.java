package lib;

public class BombCell extends AbstractCell {
    public BombCell() {
        super();
        this.bomb = true;
    }

    public String toString() {
        return isRevealed() ? "💣" : ".";
    }
}
