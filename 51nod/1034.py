def mod_inv(x, m) :
    y, u, v = m, 1, 0
    while y != 0 :
        r = x // y
        x, y = y, x - y * r
        u, v = v, u - v * r
    assert x == 1
    return u % m

def mat_mod_det(A, m) :
    coeff = 1
    for i in range(n) :
        k = -1
        for j in range(i, n) :
            if A[j][i] :
                k = j
                break
        if k == -1 :
            return 0
        if i != k :
            for j in range(i, n) :
                A[i][j], A[k][j] = A[k][j], A[i][j]
            coeff = m - coeff # coeff > 0
        inver = mod_inv(A[i][i], m)
        for j in range(i + 1, n) :
            if A[j][i] == 0 :
                continue
            diff = A[j][i] * inver % m
            for k in range(i, n) :
                A[j][k] = (A[j][k] - diff * A[i][k]) % m
        coeff = coeff * A[i][i] % m
    return coeff

pr = [142047608024141168581305158224777312511, 105539732998446783265288409610093251863, 93579093834498837631140039200278283587, 164108781837932399551980775460572678547, 136766099053318233052650533103969077627, 88138189903066884413000091193837333931, 110405237958931800901159089880825411463, 152553572151682958599392416471328485743, 120778554602063775473563858153736777743, 130595817592375452250156589629477722559, 168774687205633258296884740722895132079, 94069534500464913182366308863505442467, 165196052976527913525792828404087572783, 125795370521406065609104022130727424951, 126497345814069070152776207300360544859, 131334983716251813521868417030677564491, 98621338582677210986669748111680319319, 106038848898059562493182597440243870983, 116678333768880279024688262650973209507, 154284272625987204741258778869175320431, 132527399787830869142736501743706140459, 163025879002097968758413113205390343731, 128626514497831387585527654725416714939, 111733738959866772732281029460737495507, 106936598825115577342990654226949737479, 85914035940789097329734586163709990299, 146607972984987317653730757992674359287, 111753779111054287652505369916725371167, 114972928526548135788523175597419133819, 116621006004305881926318355346765563747, 100121042047600884229170091760884563523, 134119502460985833490258199961543150067, 130451302873313689690815830357931003611, 135154939983209506475227216230130187083, 119067973395240383567732825066642654731, 129543106009562322517774611555785530967, 143463760854434003484981021146379140519, 91425838556738453706728942067104484479, 86286518160808705680779793725781500311, 110686083761487720730282465694896208039, 108691941911945615973643476261717025747, 118495558569980274729507698273104258991, 153960161111228974455340531534942856039, 123773792350257907785839572633798980151, 125166038374051731034683039771214159663, 88905594330737957350346921345746028887, 155565375847200749220119204255388812579, 92303786910412076033342223840969560947, 159571492299594048584556643935579321947, 103580822302150334587686519826130055539, 162200045836310413765055929523337346451, 135540186554839231007230598850280082971, 159334445902431175949838057938112348419, 150405859408843337303728933235684938703, 101295480896714542221194717190823237259, 111095179129704207068107614979993689371, 129362585708645696172202638502174020859, 100722144571697966871865393682351531651, 147620373075932566634278562899842634607, 151813443664120393955485611397529623871, 98057018684285559428882966621603694187, 123527642335360669001876494595495375971, 140821593271791993412410640020375793571, 149878125860709251256222129151659592987, 128880478216905535487508282174143389159, 92333393465254904444509179255448830911]
def mat_det(A, B) :
    ans, mod = 0, 1
    for pp in pr :
        for i in range(n) :
            for j in range(n) :
                B[i][j] = A[i][j] #% pp
        rr = mat_mod_det(B, pp)
        if rr and pow(rr, (pp - 1) >> 1, pp) != 1 : # ans is a square number after abs
            rr = pp - rr
        rr = mod_inv(mod, pp) * (rr - ans) % pp
        if not rr :
            break
        ans, mod = rr * mod + ans, mod * pp
    return ans

def mat_trans(A, B) : # B = B + T * A
    for i in range(n) :
        for j in range(n) :
            val = B[i][j]
            if j > 0 :
                val += A[i][j - 1]
            if j + 1 < n :
                val += A[i][j + 1]
            B[i][j] = val

if __name__ == "__main__" :
    n, m = map(int, input().split(" "))
    if ((n * m) & 1) == 1 :
        print(0)
        exit(0)
    if n > m :
        n, m = m, n
    A = [[1 if i == j else 0 for j in range(n)] for i in range(n)]
    B = [[1 if abs(i - j) == 1 else 0 for j in range(n)] for i in range(n)]
    #print(B)
    for i in range(1, m) :
        A, B = B, A
        mat_trans(A, B)
        #print(B)
    val = mat_det(B, A)
    #print(val)
    import math
    ans = 10 ** int(math.log10(val) / 2)
    while not (ans ** 2 <= val and (ans + 1) ** 2 > val) :
        ans = (ans + val // ans) >> 1
    print(ans)
