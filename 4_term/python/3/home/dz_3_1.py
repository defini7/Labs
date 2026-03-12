iota_count = -1

def iota():
    global iota_count
    iota_count += 1
    return iota_count


TT_NUMBER = iota()
TT_OP_MUL = iota()
TT_OP_DIV = iota()
TT_OP_ADD = iota()
TT_OP_SUB = iota()
TT_OP_UADD = iota()
TT_OP_USUB = iota()
TT_LPAREN = iota()
TT_RPAREN = iota()
    
# PEDMAS, BODMAS
OPS = {
    TT_OP_ADD: (0, 2),
    TT_OP_SUB: (0, 2),
    TT_OP_MUL: (1, 2),
    TT_OP_DIV: (1, 2),
    TT_OP_UADD: (2, 1),
    TT_OP_USUB: (2, 1)
}


TEXT = iota()
CURSOR = iota()


def empty(state):
    return state[CURSOR] >= len(state[TEXT])


def chop(state):
    if not empty(state):
        state[CURSOR] += 1


def char(state):
    return state[TEXT][state[CURSOR]]


def trim_left(state):
    while not empty(state) and char(state).isspace():
        chop(state)


def next_token(state):
    trim_left(state)

    if empty(state):
        return None
    
    first = char(state)

    if first.isdigit():
        start = state[CURSOR]

        while not empty(state) and char(state).isdigit():
            chop(state)

        return (TT_NUMBER, state[TEXT][start:state[CURSOR]])
    
    lookup = {
        "(": TT_LPAREN,
        ")": TT_RPAREN,
        "+": TT_OP_ADD,
        "-": TT_OP_SUB,
        "*": TT_OP_MUL,
        "/": TT_OP_DIV
    }

    token_type = lookup.get(first)

    if token_type is not None:
        chop(state)
        return (token_type, None)
    
    raise SyntaxError("unexpected character")


def evaluate(tokens):
    holding, output, solving = [], [], []
    prev = None

    for token in tokens:
        match token[0]:
            case x if x == TT_NUMBER:
                output.append(token)

            case x if x == TT_LPAREN:
                holding.append(token)

            case x if x == TT_RPAREN:
                while holding[-1][0] != TT_LPAREN:
                    output.append(holding.pop())

                holding.pop() # )

            case x if x in (TT_OP_ADD, TT_OP_SUB, TT_OP_MUL, TT_OP_DIV, TT_OP_UADD, TT_OP_USUB):
                while len(holding) > 0:
                    tok = holding[-1]

                    if tok[0] != TT_LPAREN and tok[0] <= OPS[tok[0]][0]:
                        output.append(tok)
                        holding.pop()
                    else:
                        break

                uop = False

                if token[0] in (TT_OP_ADD, TT_OP_SUB):
                    if prev is None or prev[0] not in (TT_NUMBER, TT_RPAREN):
                        holding.append((TT_OP_UADD if token[0] == TT_OP_ADD else TT_OP_USUB, None))
                        uop = True

                if not uop:
                    holding.append(token)

        prev = token

    while len(holding) > 0:
        output.append(holding.pop())

    for token in output:
        if token[0] == TT_NUMBER:
            solving.append(int(token[1]))
        else:
            if token[0] in (TT_OP_UADD, TT_OP_USUB):
                solving.append(-solving.pop())
            else:
                rhs = solving.pop()
                lhs = solving.pop()

                match token[0]:
                    case x if x == TT_OP_ADD:
                        solving.append(lhs + rhs)
                        print(f"{lhs} + {rhs} = {solving[-1]}")

                    case x if x == TT_OP_SUB:
                        solving.append(lhs - rhs)
                        print(f"{lhs} - {rhs} = {solving[-1]}")

                    case x if x == TT_OP_MUL:
                        solving.append(lhs * rhs)
                        print(f"{lhs} * {rhs} = {solving[-1]}")

                    case x if x == TT_OP_DIV:
                        solving.append(lhs / rhs)
                        print(f"{lhs} / {rhs} = {solving[-1]}")


parser = {
    CURSOR: 0,
    TEXT: "1 *   (2  +3  )  -   (  7+     (5-2*2)  *2)",
}

tokens = []

while True:
    token = next_token(parser)

    if token is None:
        break

    tokens.append(token)

evaluate(tokens)
