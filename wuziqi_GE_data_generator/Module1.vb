Imports System.Text
Module Module1

    Sub MyDebug()
        Dim a As Integer() = {1, 0, 1, 2, 1, 0, 1, 2, 1, 0, 1, 2, 1, 0, 1}
        Console.WriteLine(a.ToString)
        Console.WriteLine(GetChessString(a))
        Console.WriteLine(GetChessString(GetChessIntX(14348905， 15)))
        Console.Read()
        End
    End Sub

    Sub Main()
        GenerateWinJudge()
        End

        Dim x As Integer
        Try
            Do
                Console.Clear()
                Console.Write("请输入x（5~15之间的整数）：")
                x = Console.ReadLine()
                If Not (5 <= x <= 15) Then
                    Console.WriteLine("输入错误")
                    Console.Read()
                    End
                End If
                FigureAllGEIntXAndSaveToFile(x)
                Console.WriteLine("完成！继续请输入y，退出请按任意键")
            Loop While Console.ReadLine() = "y"

        Catch ex As Exception
            Console.WriteLine(ex.ToString)
            Console.Read()
        End Try

        Console.Read()
        Console.Read()
    End Sub

    Sub GenerateWinJudge()
        'init
        Dim chessInt15 As Integer()
        Dim chessString As String
        Dim progress As Double
        Dim MyFileStream As New IO.FileStream("JudgeLineData.c", IO.FileMode.CreateNew)
        Dim MyStreamWriter As New IO.StreamWriter(MyFileStream)

        'write title
        MyStreamWriter.Write("#include ")
        MyStreamWriter.Write(Chr(34))
        MyStreamWriter.Write("pch.h")
        MyStreamWriter.WriteLine(Chr(34))
        MyStreamWriter.WriteLine("short JudgeData[14348907] = {")

        '
        For i = 0 To 3 ^ 15 - 1
            chessInt15 = GetChessIntX(i, 15)
            chessString = GetChessString(chessInt15)

            If i Mod 20 = 0 And i <> 0 Then MyStreamWriter.WriteLine()

            progress = i / (3 ^ 15 - 1) * 100
            Console.Title = String.Format("progress: {0:n3}%", progress)

            Console.Write(chessString)
            Console.Write(" : ")
            If chessString.Contains("11111") Then
                MyStreamWriter.Write("1")
                Console.WriteLine("1")
            ElseIf chessString.Contains("22222") Then
                MyStreamWriter.Write("2")
                Console.WriteLine("2")
            Else
                MyStreamWriter.Write("0")
                Console.WriteLine("0")
            End If
            If i < 3 ^ 15 - 1 Then MyStreamWriter.Write(",")
            If i Mod 10000 = 0 Then MyStreamWriter.Flush()

        Next

        'write tail
        MyStreamWriter.Write("};")

        'save and close file
        MyStreamWriter.Flush()
        MyStreamWriter.Dispose()
        MyFileStream.Dispose()

    End Sub

    Sub FigureAllGEIntXAndSaveToFile(x As Integer)

        'init
        Dim i, tmpScore As Integer
        Dim startNum As Integer, endNum As Integer
        Dim progress As Double
        Dim MyFileStream As New IO.FileStream("GEInt" & x.ToString & "Data_Black.c", IO.FileMode.CreateNew)
        Dim MyStreamWriter As New IO.StreamWriter(MyFileStream)
        Dim myDelegateGetGE As DelegateGetGE = GetDelegateGetGE(x)

        'write title
        MyStreamWriter.Write("#include ")
        MyStreamWriter.Write(Chr(34))
        MyStreamWriter.Write("pch.h")
        MyStreamWriter.WriteLine(Chr(34))
        MyStreamWriter.Write("short GEInt{0}_Data_Black[{1}] = ", x, 3 ^ x)
        MyStreamWriter.WriteLine("{")

        startNum = 0
        endNum = 3 ^ x - 1
        For i = startNum To endNum
            If i Mod 20 = 0 And i <> 0 Then MyStreamWriter.WriteLine()
            progress = (i - startNum) / (endNum - startNum) * 100
            Console.Title = String.Format("progress: {0:n3}%", progress)

            Dim chessIntX As Integer() = GetChessIntX(i, x)
            tmpScore = myDelegateGetGE.Invoke(chessIntX)
            Console.Write(GetChessString(chessIntX))
            Console.Write(" : ")
            Console.WriteLine(tmpScore)

            MyStreamWriter.Write(tmpScore)
            If i < endNum Then MyStreamWriter.Write(",")
            If i Mod 10000 = 0 Then MyStreamWriter.Flush()
        Next

        MyStreamWriter.Flush()
        MyStreamWriter.Write("};")

        MyStreamWriter.Dispose()
        MyFileStream.Dispose()

    End Sub

    Function GetChessIntX(num As Integer, x As Integer) As Integer()
        Dim result(x - 1) As Integer

        Dim r, i As Integer
        i = x - 1

        While num > 0
            r = num Mod 3
            result(i) = r
            i -= 1
            num \= 3
        End While

        Return result
    End Function

    Function GetChessString(chessIntX As Integer()) As String
        Dim resultBuilder As New StringBuilder(chessIntX.Length)
        For Each s In chessIntX
            resultBuilder.Append(s.ToString())
        Next
        Return resultBuilder.ToString()
    End Function

    Function GetGE_Int15_Black(chessInt15 As Integer()) As Integer
        'init
        Dim chessString As String = GetChessString(chessInt15)
        Dim result As Integer = 0

        'win 5
        If chessString.Contains("11111") Then
            Return 10000
        End If
        If chessString.Contains("22222") Then
            Return -10000
        End If

        'live 4
        If chessString.Contains("011110") Then
            result += 5000
        End If
        If chessString.Contains("022220") Then
            result -= 5000
        End If

        'sleep 4
        If chessString.Contains("011112") Or chessString.Contains("211110") Or chessString.Contains("11101") Or chessString.Contains("10111") Or chessString.Contains("11011") Then
            result += 1800
        End If
        If chessString.Contains("022221") Or chessString.Contains("122220") Or chessString.Contains("22202") Or chessString.Contains("20222") Or chessString.Contains("22022") Then
            result -= 1800
        End If

        'live 3
        If chessString.Contains("01110") Then
            result += 1000
        End If
        If chessString.Contains("02220") Then
            result -= 1000
        End If

        'sleep 3
        If chessString.Contains("211100") Or chessString.Contains("001112") Or chessString.Contains("211010") Or chessString.Contains("010112") Or chessString.Contains("210110") Or chessString.Contains("011012") Or chessString.Contains("11001") Or chessString.Contains("10011") Or chessString.Contains("10101") Or chessString.Contains("2011102") Then
            result += 500
        End If
        If chessString.Contains("122200") Or chessString.Contains("002221") Or chessString.Contains("122020") Or chessString.Contains("020221") Or chessString.Contains("120220") Or chessString.Contains("022021") Or chessString.Contains("22002") Or chessString.Contains("20022") Or chessString.Contains("20202") Or chessString.Contains("1022201") Then
            result -= 500
        End If

        'live 2
        If chessString.Contains("001100") Or chessString.Contains("01010") Or chessString.Contains("1001") Then
            result += 100
        End If
        If chessString.Contains("002200") Or chessString.Contains("02020") Or chessString.Contains("2002") Then
            result -= 100
        End If

        'sleep 2
        If chessString.Contains("211000") Or chessString.Contains("000112") Or chessString.Contains("210100") Or chessString.Contains("001012") Or chessString.Contains("210010") Or chessString.Contains("010012") Or chessString.Contains("10001") Then
            result += 30
        End If
        If chessString.Contains("122000") Or chessString.Contains("000221") Or chessString.Contains("120200") Or chessString.Contains("002021") Or chessString.Contains("120020") Or chessString.Contains("020021") Or chessString.Contains("20002") Then
            result -= 30
        End If

        Return result
    End Function

    Delegate Function DelegateGetGE(chessIntX As Integer()) As Integer

    Function GetDelegateGetGE(x As Integer) As DelegateGetGE
        Select Case x
            Case 5
                Return AddressOf GetGE_Int5_Black
            Case 6 To 15
                Return AddressOf GetGE_Int15_Black
            Case Else
                Throw New Exception("没有对应 x = " & x.ToString & " 的GetGE函数")
        End Select
    End Function

    Function GetGE_Int5_Black(chessInt5 As Integer()) As Integer
        'init
        Dim chessString As String = GetChessString(chessInt5)
        Dim counter As Integer = 0

        'polluted
        If chessString.Contains("1") And chessString.Contains("2") Then Return 0

        For Each s In chessInt5
            counter += s
        Next

        'empty
        If counter <= 0 Then Return 0

        If chessString.Contains("2") Then counter /= 2

        Dim result As Integer
        Select Case counter
            Case 5
                result = 10000
            Case 4
                result = 1800
            Case 3
                result = 500
            Case 2
                result = 100
            Case Else
                result = 0
        End Select

        If chessString.Contains("2") Then result = -result

        Return result
    End Function


End Module
