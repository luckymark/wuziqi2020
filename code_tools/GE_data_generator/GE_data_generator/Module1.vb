Imports System.Text
Module Module1

    Sub MyDebug()
        Dim a As Integer() = {1, 0, 1, 2, 1, 0, 1, 2, 1, 0, 1, 2, 1, 0, 1}
        Console.WriteLine(a.ToString)
        Console.WriteLine(GetChessString(a))
        Console.WriteLine(GetChessString(GetChessInt15(14348905)))
        Console.Read()
        End
    End Sub

    Sub Main()
        Dim startNum, endNum As Integer

        Try
            Console.Write("开始：")
            startNum = Console.ReadLine()
            Console.WriteLine()
            Console.Write("结束：")
            endNum = Console.ReadLine()
            FigureAllGEAndSaveToFile(startNum, endNum)
        Catch ex As Exception
            Console.WriteLine(ex.ToString)
            Console.Read()
        End Try

        Console.Read()
        Console.Read()
    End Sub

    Sub FigureAllGEAndSaveToFile(startNum As Integer, endNum As Integer)
        'init
        Dim i, tmpScore As Integer
        Dim progress As Double
        Dim chessInt15(15) As Integer
        Dim MyFileStream As New IO.FileStream("GE_Int15_Data_" & startNum.ToString() & "_" & endNum.ToString() & ".txt", IO.FileMode.CreateNew)
        Dim MyStreamWriter As New IO.StreamWriter(MyFileStream)

        For i = startNum To endNum
            progress = (i - startNum) / (endNum - startNum) * 100
            Console.Title = String.Format("progress: {0:n3}%", progress)

            chessInt15 = GetChessInt15(i)
            tmpScore = GetScore_BlackPlayer(chessInt15)
            Console.Write(GetChessString(chessInt15))
            Console.Write(" : ")
            Console.WriteLine(tmpScore)

            MyStreamWriter.Write(tmpScore & ",")
            If i Mod 10 = 0 Then MyStreamWriter.WriteLine()
            If i Mod 10000 = 0 Then MyStreamWriter.Flush()
        Next

        MyStreamWriter.Flush()
        MyStreamWriter.Dispose()
        MyFileStream.Dispose()

    End Sub


    Function GetChessInt15(num As Integer) As Integer()
        Dim result(14) As Integer

        Dim r, i As Integer
        i = 14

        While num > 0
            r = num Mod 3
            result(i) = r
            i -= 1
            num \= 3
        End While

        Return result
    End Function

    Function GetChessString(chessInt15 As Integer()) As String
        Dim resultBuilder As New StringBuilder(15)
        For Each s In chessInt15
            resultBuilder.Append(s.ToString())
        Next
        Return resultBuilder.ToString()
    End Function

    Function GetScore_BlackPlayer(chessInt15 As Integer()) As Integer
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

End Module
