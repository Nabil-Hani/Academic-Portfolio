package lib;

import exceptions.*;
import java.util.*;

public class Demineur {
    private final int rows;
    private final int cols;
    private final int bombs;
    private final AbstractCell[][] grid;
    private boolean[][] visited;
    private boolean firstClick = true;
    private int clickCount = 0;
    private int cellsToReveal;

    public Demineur(int rows, int cols, int bombs) {
        this.rows = rows;
        this.cols = cols;
        this.bombs = bombs;
        this.grid = new AbstractCell[rows][cols];
        initGrid();
    }

    private void initGrid() {
        for (int r = 0; r < rows; r++)
            for (int c = 0; c < cols; c++)
                grid[r][c] = new StandardCell();
    
        this.cellsToReveal = rows * cols - bombs;
    }
    

    public int getRowCount() { return rows; }
    public int getColCount() { return cols; }
    public int getBombCount() { return bombs; }
    public int getClickCount() { return clickCount; }

    public AbstractCell getCell(int row, int col) {
        return grid[row][col];
    }

    public void revealCell(int row, int col) throws InvalidMoveException {

        if (grid[row][col].isFlagged())
            throw new InvalidMoveException("Vous ne pouvez pas révéler une case marquée.");

        if (grid[row][col].isRevealed())
            throw new InvalidMoveException("Cette case est déjà révélée.");

        if (firstClick) {
            placeBombs(row, col);
            calculateAdjacentCounts();
            firstClick = false;
        }

        clickCount++;

        if (grid[row][col].isBomb()) {
            throw new GameLostException();
        }

        revealRecursive(row, col);

        if (cellsToReveal == 0)
            throw new GameWonException();
    }

    private void revealRecursive(int row, int col) {
        if (!isValid(row, col) || visited[row][col] || grid[row][col].isRevealed())
            return;

        visited[row][col] = true;
        grid[row][col].reveal();
        cellsToReveal--;

        if (grid[row][col].getAdjacentBombs() == 0) {
            for (int dr = -1; dr <= 1; dr++)
                for (int dc = -1; dc <= 1; dc++)
                    if (!(dr == 0 && dc == 0))
                        revealRecursive(row + dr, col + dc);
        }
    }

    private void placeBombs(int safeRow, int safeCol) {
        List<int[]> positions = new ArrayList<>();
        for (int r = 0; r < rows; r++)
            for (int c = 0; c < cols; c++)
                if (!(r == safeRow && c == safeCol))
                    positions.add(new int[]{r, c});
    
        Collections.shuffle(positions);
        for (int i = 0; i < bombs; i++) {
            int[] pos = positions.get(i);
            grid[pos[0]][pos[1]] = new BombCell(); 
        }
    }
    

    private void calculateAdjacentCounts() {
        for (int r = 0; r < rows; r++)
            for (int c = 0; c < cols; c++)
                if (!grid[r][c].isBomb()) {
                    int count = 0;
                    for (int dr = -1; dr <= 1; dr++)
                        for (int dc = -1; dc <= 1; dc++) {
                            int nr = r + dr, nc = c + dc;
                            if (isValid(nr, nc) && grid[nr][nc].isBomb())
                                count++;
                        }
                    grid[r][c].setAdjacentBombs(count);
                }

        visited = new boolean[rows][cols];
    }

    private boolean isValid(int r, int c) {
        return r >= 0 && c >= 0 && r < rows && c < cols;
    }

    public int[] attemptRandomReveal() {
        List<int[]> options = new ArrayList<>();
        for (int r = 0; r < rows; r++)
            for (int c = 0; c < cols; c++)
                if (!grid[r][c].isRevealed() && !grid[r][c].isBomb())
                    options.add(new int[]{r, c});

        if (options.isEmpty()) return null;
        return options.get(new Random().nextInt(options.size()));
    }
}
