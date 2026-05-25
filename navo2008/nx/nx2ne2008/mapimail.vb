Imports System.Runtime.InteropServices
Imports nxappcore
'base class for communication with navoinet.mail (MAPI wrapper)

Namespace nxmail


Public Class mapimail_
    Protected Sub New()
        m_oNAVOInetMapi = CreateObject("navoinet.mail")
    End Sub

    Protected m_oNAVOInetMapi As Object
End Class


'mail message wrapper
<ComVisible(True), Guid(global_config.gc_guid_nx2ne2002_nxmailmsg)> _
Public Class nxmailmsg
    <ComVisible(True), Guid(global_config.gc_guid_nx2ne2002_nxmail_attachment)> _
    Public Class nxmail_attachment
        Public Sub New()
        End Sub

        Public Property displayname() As String
            Get
                Return m_strDisplayName
            End Get
            Set(ByVal Value As String)
                m_strDisplayName = Value
            End Set
        End Property
        Public Property localfilename() As String
            Get
                Return m_strLocalFileName
            End Get
            Set(ByVal Value As String)
                m_strLocalFileName = Value
            End Set
        End Property
        'used when sending
        Public Sub set_source(ByVal varSourceDataRef As Object)
            m_varSourceDataRef = varSourceDataRef
        End Sub
        Public Function get_source() As Object
            Return m_varSourceDataRef
        End Function
        'used when receiving
        Public Sub attach_destination_stream(ByVal oDestStream As Object)
            oDestStream.Attach(m_strLocalFileName)
        End Sub

        Private m_strDisplayName As String
        Private m_strLocalFileName As String
        Private m_varSourceDataRef As Object
    End Class
    <ComVisible(True), Guid(global_config.gc_guid_nx2ne2002_nxmail_attachment_collection)> _
    Public Class nxmail_attachment_collection
        Inherits nxarray
        Default Public Shadows ReadOnly Property item(ByVal iIndex As Int32) As nxmail_attachment
            Get
                Return MyBase.Item(iIndex)
            End Get
        End Property
    End Class
    <ComVisible(True), Guid(global_config.gc_guid_nx2ne2002_nxmail_address)> _
Public Class nxmail_address
        Public Sub New()
        End Sub

        Public Property address()
            Get
                Return m_strMailAddress
            End Get
            Set(ByVal Value)
                m_strMailAddress = Value
            End Set
        End Property
        Public Property displayname()
            Get
                Return m_strDisplayName
            End Get
            Set(ByVal Value)
                m_strDisplayName = Value
            End Set
        End Property

        Private m_strMailAddress As String
        Private m_strDisplayName As String

    End Class
    <ComVisible(True), Guid(global_config.gc_guid_nx2ne2002_nxmail_address_collection)> _
        Public Class nxmail_address_collection
        Inherits nxarray

        Default Public Shadows ReadOnly Property Item(ByVal iIndex As Int32) As nxmail_address
            Get
                Return MyBase.Item(iIndex)
            End Get
        End Property
    End Class
    Public Sub New()
        m_oSender = Nothing
        m_oReceipentArr = New nxmail_address_collection
        m_oAttachments = New nxmail_attachment_collection
        m_iFormat = 1
        m_iRecvAttachmentCount = -1
    End Sub

    'simple wrapper - one receipent msg
    Public Shared Function create_msg(ByVal strReceipentAddr As String, _
        ByVal strSubject As String, ByVal strBody As String) As nxmailmsg
        Dim oMessage As nxmailmsg
        oMessage = New nxmailmsg

        Dim oReceipent As nxmail_address
        oReceipent = New nxmail_address
        oReceipent.address = strReceipentAddr
        oReceipent.displayname = strReceipentAddr

        oMessage.receipents.add(oReceipent)
        oMessage.subject = strSubject
        oMessage.body = strBody

        Return oMessage
    End Function

    Public Function add_attachment(ByVal strDisplayName As String, _
        ByVal varSourceDataRef As Object) As nxmail_attachment
        Dim oAttachment As nxmail_attachment
        oAttachment = New nxmail_attachment
        oAttachment.displayname = strDisplayName
        oAttachment.set_source(varSourceDataRef)
        attachments.add(oAttachment)
        Return oAttachment
    End Function

    Public Property sender() As nxmail_address
        Get
            Return m_oSender
        End Get
        Set(ByVal Value As nxmail_address)
            m_oSender = Value
        End Set
    End Property
    Public ReadOnly Property receipents() As nxmail_address_collection
        Get
            Return m_oReceipentArr
        End Get
    End Property
    Public ReadOnly Property attachments() As nxmail_attachment_collection
        Get
            Return m_oAttachments
        End Get
    End Property
    Public Property subject() As String
        Get
            Return m_strSubject
        End Get
        Set(ByVal Value As String)
            m_strSubject = Value
        End Set
    End Property
    Public Property body() As String
        Get
            Return m_strBody
        End Get
        Set(ByVal Value As String)
            m_strBody = Value
        End Set
    End Property
    Public Property format() As Integer
        Get
            Return m_iFormat
        End Get
        Set(ByVal Value As Integer)
            m_iFormat = Value
        End Set
    End Property
    Public Property datereceived() As Date
        Get
            Return m_dDateReceived
        End Get
        Set(ByVal Value As Date)
            m_dDateReceived = Value
        End Set
    End Property
    Public Property recvattcount() As Integer
        Get
            Return m_iRecvAttachmentCount
        End Get
        Set(ByVal Value As Integer)
            m_iRecvAttachmentCount = Value
        End Set
    End Property

    Private m_oSender As nxmail_address
    Private m_oReceipentArr As nxmail_address_collection
    Private m_oAttachments As nxmail_attachment_collection
    Private m_strSubject As String
    Private m_strBody As String
    Private m_dDateReceived As Date
    Private m_iFormat As Integer
    Private m_iRecvAttachmentCount As Integer   'liczba zal. w otrzymanym mailu
End Class

'read mail support
<ComVisible(True), Guid(global_config.gc_guid_nx2ne2002_nxreadmail)> _
Public Class nxreadmail
    Inherits mapimail_
    Implements IEnumerable

    Public Sub New(ByVal bUnreadOnly As Boolean)
        MyBase.New()
        m_bUnreadOnly = bUnreadOnly
    End Sub
    Public Function connect(ByVal strUser As String, ByVal strPassword As String) As Boolean
        Return m_oNAVOInetMapi.download(strUser, strPassword)
    End Function

    Public Function read_message(ByVal iIndex As Integer, ByVal bLoadAttachments As Boolean) As nxmailmsg
        Dim varSenderAddress As Object
        Dim varSenderDisplay As Object
        Dim varSubject As Object
        Dim varMsgBody As Object
        Dim varDateReceived As Object
        Dim varAttachmentCount As Object

        Dim bResult As Boolean = m_oNAVOInetMapi.read(iIndex, m_bUnreadOnly, _
                varSenderAddress, varSenderDisplay, _
                varSubject, varMsgBody, varDateReceived, varAttachmentCount)

        If bResult Then
            Dim oMessage As nxmailmsg = New nxmailmsg
            With oMessage
                .sender = New nxmailmsg.nxmail_address
                .sender.address = DirectCast(varSenderAddress, String)
                .sender.displayname = DirectCast(varSenderDisplay, String)
                .subject = DirectCast(varSubject, String)
                .body = DirectCast(varMsgBody, String)
                .datereceived = DirectCast(varDateReceived, Date)
                .recvattcount = DirectCast(varAttachmentCount, Integer)

                If bLoadAttachments Then
                    Dim varAttName As Object
                    Dim varAttStreamFileName As Object
                    For iter As Integer = 1 To .recvattcount

                        m_oNAVOInetMapi.getattachment(iter, varAttName, varAttStreamFileName)
                        Dim strAttName As String = DirectCast(varAttName, String)
                        Dim strAttStreamFileName As String = DirectCast(varAttStreamFileName, String)

                        Dim oAttachment As nxmailmsg.nxmail_attachment
                        oAttachment = New nxmailmsg.nxmail_attachment
                        oAttachment.displayname = strAttName
                        oAttachment.localfilename = strAttStreamFileName

                        .attachments.add(oAttachment)
                    Next
                End If
            End With

            Return oMessage
        Else
            Return Nothing
        End If
    End Function

    Public Function GetEnumerator() As System.Collections.IEnumerator Implements System.Collections.IEnumerable.GetEnumerator
        Return New nxreadmail_enumerator(Me)
    End Function

    <ComVisible(True), Guid(global_config.gc_guid_nx2ne2002_nxreadmail_enumerator)> _
        Public Class nxreadmail_enumerator
        Implements IEnumerator

        Public Sub New(ByVal oParent As nxreadmail)
            m_oParent = oParent
            Reset()
        End Sub
        Public ReadOnly Property Current() As Object Implements System.Collections.IEnumerator.Current
            Get
                Return m_oCurrentMsg
            End Get
        End Property

        Public Function MoveNext() As Boolean Implements System.Collections.IEnumerator.MoveNext
            m_iPosition += 1
            m_oCurrentMsg = m_oParent.read_message(m_iPosition, True)
            Return Not (m_oCurrentMsg Is Nothing)
        End Function

        Public Sub Reset() Implements System.Collections.IEnumerator.Reset
            m_iPosition = 0
            m_oCurrentMsg = Nothing
        End Sub

        Private ReadOnly m_oParent As nxreadmail
        Private m_iPosition As Integer
        Private m_oCurrentMsg As nxmailmsg
    End Class

    Private m_bUnreadOnly As Boolean
End Class

'send mail support
<ComVisible(True), Guid(global_config.gc_guid_nx2ne2002_nxsendmail)> _
Public Class nxsendmail
    Inherits mapimail_
    Public Sub New()
        MyBase.New()
    End Sub
    Public Function connect(ByVal strUser As String, ByVal strPassword As String) As Boolean
        Return m_oNAVOInetMapi.connect(strUser, strPassword)
    End Function

    Public Function send(ByVal oNXMailMessageObj As Object) As Boolean
        Dim oNXMailMessage As nxmailmsg = oNXMailMessageObj
        For Each oReceipent As nxmailmsg.nxmail_address In oNXMailMessage.receipents
            m_oNAVOInetMapi.addrecip(oReceipent.address, oReceipent.displayname)
        Next
        For Each oAttachment As nxmailmsg.nxmail_attachment In oNXMailMessage.attachments
            m_oNAVOInetMapi.addattachment(oAttachment.displayname, oAttachment.get_source())
        Next
        Return m_oNAVOInetMapi.send(oNXMailMessage.subject, oNXMailMessage.body, _
            oNXMailMessage.format)
    End Function
End Class

End Namespace
