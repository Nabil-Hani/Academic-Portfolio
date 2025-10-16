package lib;

public abstract class AbstractCell {
    protected boolean revealed = false;
    protected boolean bomb = false;
    protected boolean flagged = false;
    protected int adjacentBombs = 0;

    public boolean isRevealed() {
        return revealed;
    }

    public boolean isBomb() {
        return bomb;
    }

    public boolean isFlagged() {
        return flagged;
    }

    public int getAdjacentBombs() {
        return adjacentBombs;
    }

    public void setBomb(boolean bomb) {
        this.bomb = bomb;
    }

    public void setAdjacentBombs(int count) {
        this.adjacentBombs = count;
    }

    public void reveal() {
        this.revealed = true;
    }

    public void toggleFlag() {
        if (!revealed) {
            this.flagged = !flagged;
        }
    }
}
