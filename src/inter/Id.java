package inter;

import lexer.Token;
import symbols.Type;

public class Id extends Expr {

	public int offset; // relative address

	public Id(Token id, Type p, int b) {
		super(id, p);
		offset = b;
	}

	// public String toString() {return "" + op.toString() + offset;}
}
