from math import log, sin


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

TT_FN_SIN = iota()
TT_FN_LN = iota()

OP_PRECEDENCE = {
    TT_OP_ADD: (0, 2),
    TT_OP_SUB: (0, 2),
    TT_OP_MUL: (1, 2),
    TT_OP_DIV: (1, 2),
    TT_OP_UADD: (2, 1),
    TT_OP_USUB: (2, 1)
}

FUNC_TO_TT = {
    "sin": TT_FN_SIN,
    "ln": TT_FN_LN
}

OP_TO_TT = {
    "(": TT_LPAREN,
    ")": TT_RPAREN,
    "+": TT_OP_ADD,
    "-": TT_OP_SUB,
    "*": TT_OP_MUL,
    "/": TT_OP_DIV
}

TT_TO_FUNC = {
    TT_FN_SIN: sin,
    TT_FN_LN: log,
    TT_OP_ADD: lambda x, y: x + y,
    TT_OP_SUB: lambda x, y: x - y,
    TT_OP_MUL: lambda x, y: x * y,
    TT_OP_DIV: lambda x, y: x / y
}


TEXT = iota()
CURSOR = iota()


def is_func(token):
    return token[0] in (TT_FN_LN, TT_FN_SIN)


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

        period = False

        while not empty(state) and (char(state).isdigit() or char(state) == '.'):
            if char(state) == '.':
                if period:
                    raise SyntaxError("can't have 2 periods in 1 number")

                period = True

            chop(state)

        return TT_NUMBER, state[TEXT][start:state[CURSOR]]
    
    if first.isalpha():
        start = state[CURSOR]

        while not empty(state) and char(state).isalpha():
            chop(state)

        name = state[TEXT][start:state[CURSOR]]

        token_type = FUNC_TO_TT.get(name)

        if token_type is None:
            raise NameError(f"no such function {name}")

        return token_type, None

    token_type = OP_TO_TT.get(first)

    if token_type is not None:
        chop(state)
        return (token_type, None)
    
    raise SyntaxError(f"unexpected character {first}")


def evaluate(tokens):
    holding, output, solving = [], [], []
    prev = None

    for token in tokens:
        match token[0]:
            case x if x == TT_NUMBER:
                output.append(token)

            case x if x in (TT_LPAREN, TT_FN_LN, TT_FN_SIN):
                holding.append(token)

            case x if x == TT_RPAREN:
                while holding[-1][0] != TT_LPAREN:
                    output.append(holding.pop())

                holding.pop() # )

                if len(holding) > 0 and is_func(holding[-1]):
                    output.append(holding.pop())

            case x if x in (TT_OP_ADD, TT_OP_SUB, TT_OP_MUL, TT_OP_DIV, TT_OP_UADD, TT_OP_USUB):
                while len(holding) > 0:
                    tok = holding[-1]

                    if is_func(tok) or tok[0] != TT_LPAREN and tok[0] <= OP_PRECEDENCE[tok[0]][0]:
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
            solving.append(float(token[1]))
        elif is_func(token):
            if len(solving) == 0:
                raise SyntaxError(f"not enough arguments for function call")
            
            arg = solving.pop()
            solving.append(TT_TO_FUNC[token[0]](arg))
        else:
            if token[0] in (TT_OP_UADD, TT_OP_USUB):
                solving.append(-solving.pop())
            else:
                rhs = solving.pop()
                lhs = solving.pop()

                solving.append(TT_TO_FUNC[token[0]](lhs, rhs))

    return solving.pop() if len(solving) > 0 else None


parser = {
    CURSOR: 0,
    TEXT: "1 - sin(3.1415926535)",
}

tokens = []

while True:
    token = next_token(parser)

    if token is None:
        break

    tokens.append(token)

print(evaluate(tokens))
