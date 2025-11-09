# How to Run the Full Application

You need to run **TWO servers** simultaneously:

## Step 1: Start the C++ Backend Server

Open a terminal/command prompt and run:

```batch
cd backend
run_server.bat
```

This starts the API server on **http://localhost:8080**

You should see:
```
BookWise Backend Server starting on http://localhost:8080
API endpoints available at http://localhost:8080/api
```

**Keep this terminal open!** The server must stay running.

## Step 2: Start the React Frontend

Open a **NEW** terminal/command prompt (in the main project folder) and run:

```bash
npm run dev
```

This starts the web UI on **http://localhost:5173**

You should see:
```
VITE v5.x.x  ready in xxx ms

➜  Local:   http://localhost:5173/
➜  Network: use --host to expose
```

**Keep this terminal open too!**

## Step 3: Open in Browser

Open your browser and go to:
**http://localhost:5173**

(Not localhost:8080 - that's just the API!)

## Summary

- **Backend (C++)**: `localhost:8080` - API endpoints only (no web page)
- **Frontend (React)**: `localhost:5173` - The actual web page you see
- **Browser**: Open `localhost:5173` - The frontend will automatically connect to the backend API

## Important Notes

1. **Both servers must be running at the same time**
2. **Open the frontend URL (5173) in your browser**, not the backend URL (8080)
3. The backend (8080) is just for API calls - you won't see a web page there
4. The frontend (5173) is the actual web application you interact with

## Troubleshooting

**"No webpage found" on localhost:8080?**
- That's normal! Port 8080 is just the API, not a web page
- You need to access the frontend on port 5173 instead

**Frontend can't connect to backend?**
- Make sure the backend server is running (Step 1)
- Check that you see the "BookWise Backend Server starting" message
- The frontend will show errors in the browser console if it can't reach the API

**Port already in use?**
- Make sure you're not running two instances of the same server
- Close any other applications using ports 8080 or 5173

**Both servers running but still issues?**
- Check browser console (F12) for errors
- Make sure both terminals are still running
- Try refreshing the browser page
