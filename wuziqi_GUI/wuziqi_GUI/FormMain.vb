Public Class FormMain
    Const BOARD_BLOCK_SIZE As Integer = 30
    Const BOARD_BLOCK_MARGIN As Integer = 32
    Private opt As Integer = 0
    Private counter As Integer = 1

    Private Sub FormMain_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        'lock window
        Me.MaximumSize = Me.Size
        Me.MinimumSize = Me.Size

        InitializeChessboard()
    End Sub

    Sub InitializeChessboard()
        Dim tmp As MyButton
        For i = 0 To 224
            tmp = New MyButton With {
                .Text = "",
                .BackColor = Color.Blue,
                .Index = i,
                .Left = 30 + (i Mod 15) * BOARD_BLOCK_MARGIN,
                .Top = 30 + (i \ 15) * BOARD_BLOCK_MARGIN,
                .Size = New Point(BOARD_BLOCK_SIZE, BOARD_BLOCK_SIZE),
                .FlatStyle = FlatStyle.Flat
            }
            AddHandler tmp.Click, AddressOf ChessBoard_Click
            ChessBoard(i) = tmp
            Me.Controls.Add(ChessBoard(i))
        Next
    End Sub

    Private Sub ChessBoard_Click(sender As Object, e As EventArgs)
        If opt Mod 2 = 0 Then
            ChessBoard(sender.Index).BackColor = Color.Black
            ChessBoard(sender.Index).ForeColor = Color.White
        Else
            ChessBoard(sender.Index).BackColor = Color.White
            ChessBoard(sender.Index).ForeColor = Color.Black
        End If
        ChessBoard(sender.Index).Text = counter.ToString()
        opt += 1
        counter += 1
    End Sub

    Friend ChessBoard(224) As MyButton

    Class MyButton
        Inherits Button
        Property Index As Integer
    End Class

End Class
